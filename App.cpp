/*
 * The MIT License
 *
 * Copyright 2018 Kody.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "App.hpp"

#include <wx/button.h>
#include <wx/filedlg.h>
#include <wx/menu.h>
#include <wx/sizer.h>
#include <wx/textfile.h>
#include <wx/tokenzr.h>

#include "WidgetIDs.hpp"

wxIMPLEMENT_APP( App );
        
bool App::OnInit() {
    SetupWidgets();
    
    return true;
}

void App::SetupWidgets() {
    // Create the main window and widgets
    wxFrame* main_window = new wxFrame( nullptr, wxID_ANY, "Order Sheet" );
    wxBoxSizer* window_sizer = new wxBoxSizer( wxVERTICAL );
    
    SetupOrdersheet( main_window, window_sizer );
    SetupButtons( main_window, window_sizer );
    SetupMenu( main_window );

    // Connect the window to the sizer
    main_window->SetSizer( window_sizer );
    
    // Show the window
    main_window->Show( true );
}

void App::SetupOrdersheet( wxFrame* window, wxBoxSizer* sizer ) {
    // Create sheet
    ordersheet = new Ordersheet( window, ID_GRID_ORDERS );
    
    // Layout
    sizer->Add( ordersheet, 1, wxEXPAND );
    
    // Ordersheet Events
    Bind( wxEVT_BUTTON, &Ordersheet::OnAddClient, ordersheet, ID_BUTTON_CLIENT_ADD );
    Bind( wxEVT_BUTTON, &Ordersheet::OnRemoveClient, ordersheet, ID_BUTTON_CLIENT_REMOVE );
    Bind( wxEVT_BUTTON, &Ordersheet::OnAddProduct, ordersheet, ID_BUTTON_PRODUCT_ADD );
    Bind( wxEVT_BUTTON, &Ordersheet::OnRemoveProduct, ordersheet, ID_BUTTON_PRODUCT_REMOVE );
}

void App::SetupButtons( wxFrame* window, wxBoxSizer* sizer ) {
    // Create buttons
    wxButton* button_add_client = new wxButton( window, ID_BUTTON_CLIENT_ADD, "Add Client" );
    wxButton* button_remove_client = new wxButton( window, ID_BUTTON_CLIENT_REMOVE, "Remove Client" );
    wxButton* button_add_product = new wxButton( window, ID_BUTTON_PRODUCT_ADD, "Add Product" );
    wxButton* button_remove_product = new wxButton( window, ID_BUTTON_PRODUCT_REMOVE, "Remove Product" );
    
    // Organize the buttons
    wxBoxSizer* button_control_sizer = new wxBoxSizer( wxHORIZONTAL );
    button_control_sizer->Add( button_add_client );
    button_control_sizer->Add( button_remove_client );
    button_control_sizer->Add( button_add_product );
    button_control_sizer->Add( button_remove_product );
    sizer->Add( button_control_sizer );
}

void App::SetupMenu( wxFrame* window ) {
    // Create the menu
    wxMenuBar* menu_bar = new wxMenuBar;
    
    // File Menu
    wxMenu* menu_file = new wxMenu;
    menu_file->Append( wxID_NEW );
    menu_file->Append( wxID_OPEN );
    menu_file->Append( wxID_SAVE );
    menu_file->Append( wxID_SAVEAS );
    menu_bar->Append( menu_file, "&File" );
    
    // Set the menu bar to the window
    window->SetMenuBar( menu_bar );
    
    // Menu Events
    Bind( wxEVT_MENU, &App::OnFileNew, this, wxID_NEW );
    Bind( wxEVT_MENU, &App::OnFileOpen, this, wxID_OPEN );
    Bind( wxEVT_MENU, &App::OnFileSave, this, wxID_SAVE );
    Bind( wxEVT_MENU, &App::OnFileSaveAs, this, wxID_SAVEAS );
}

void App::OnFileNew( wxCommandEvent& WXUNUSED( event ) ) {
    ordersheet->ResetGrid();
    current_filename.Clear();
}

void App::OnFileOpen( wxCommandEvent& WXUNUSED( event ) ) {
    if( !PickFilenameOpen() ) {
        return;
    }
    
    OpenFromFile( current_filename );
}

void App::OnFileSave( wxCommandEvent& WXUNUSED( event ) ) {
    if( current_filename.IsEmpty() && !PickFilenameSave() ) {
        return;
    }
    
    SaveToFile( current_filename );
}

void App::OnFileSaveAs( wxCommandEvent& WXUNUSED( event ) ) {
    if( PickFilenameSave() ) {
        SaveToFile( current_filename );
    }
}

bool App::PickFilenameOpen() {
    /// TODO: Catch unsaved?
    
    wxFileDialog dialog_open( ordersheet, wxString( "Open Order Sheet" ), wxString( "" ), wxString( "" ),
                              wxString( "CSV Files (*.csv)|*.csv" ), wxFD_OPEN | wxFD_FILE_MUST_EXIST );
    
    if( dialog_open.ShowModal() == wxID_CANCEL ) {
        return false;
    }
    
    current_filename = dialog_open.GetPath();
    return true;
}

bool App::PickFilenameSave() {
    wxFileDialog dialog_save( ordersheet, wxString( "Save Order Sheet" ), wxString( "" ), wxString( "" ),
                              wxString( "CSV Files (*.csv)|*.csv" ), wxFD_SAVE | wxFD_OVERWRITE_PROMPT );
    
    if( dialog_save.ShowModal() == wxID_CANCEL ) {
        return false;
    }
    
    current_filename = dialog_save.GetPath();
    return true;
}

void App::OpenFromFile( wxString& filename ) {
    // Read the file in
    wxTextFile file_in;
    if( !file_in.Open( filename ) ) {
        wxLogError( "Cannot open file '%s'.", filename );
        return;
    }
    
    wxString line_buffer;
    wxStringTokenizer tokenizer;
    
    // Read the header line
    line_buffer = file_in.GetFirstLine();
    tokenizer.SetString( line_buffer, wxString( "," ) );
    
    // Validate first three tokens
    if( tokenizer.GetNextToken() != wxString( "Name" ) ||
        tokenizer.GetNextToken() != wxString( "Phone #" ) ||
        tokenizer.GetNextToken() != wxString( "Credit" ) ) {
        wxLogError( "Invalid file '%s'.", filename );
        return;
    }
    
    ordersheet->ResetGrid();
    
    // Read in products
    while( tokenizer.HasMoreTokens() ) {
        ordersheet->AddProduct( tokenizer.GetNextToken() );
    }
    
    // Read the client lines
    while( !file_in.Eof() ) {
        // Tokenize the line and check it
        line_buffer = file_in.GetNextLine();
        tokenizer.SetString( line_buffer, wxString( "," ) );
        if( !tokenizer.HasMoreTokens() ) {
            continue;
        }
        
        // First token is client name
        ordersheet->AddClient( tokenizer.GetNextToken() );
        
        // Subsequent tokens are cell values.
        for( int i = 0; i < ordersheet->GetNumberCols() && tokenizer.HasMoreTokens(); ++i ) {
            ordersheet->SetCellValue( ordersheet->GetNumberRows()-1, i, tokenizer.GetNextToken() );
        }
    }
}

void App::SaveToFile( wxString& filename ) {
    wxTextFile file_out;
    file_out.Create( filename );
    file_out.Clear();
    
    wxString line_buffer;
    
    // Write the first line - header
    line_buffer = "Name";
    for( int i = 0; i < ordersheet->GetNumberCols(); ++i ) {
        line_buffer += ",";
        line_buffer += ordersheet->GetColLabelValue( i );
    }
    file_out.AddLine( line_buffer );
    
    // Write each client's data
    for( int j = 0; j < ordersheet->GetNumberRows(); ++j ) {
        line_buffer.Clear();
        line_buffer += ordersheet->GetRowLabelValue( j );
        for( int i = 0; i < ordersheet->GetNumberCols(); ++i ) {
            line_buffer += ",";
            line_buffer += ordersheet->GetCellValue( j, i );
        }
        file_out.AddLine( line_buffer );
    }
    
    // Write to disk
    file_out.Write();
}
