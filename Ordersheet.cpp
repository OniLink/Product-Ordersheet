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

#include "Ordersheet.hpp"
#include <wx/textdlg.h>

#include "WidgetIDs.hpp"

const int RESERVED_COLUMNS = 2;
const int STATUS_CHOICE_COUNT = 5;
const wxString STATUS_CHOICES[] = {
    "No Order",
    "Ordered",
    "Shipped",
//    "Received",
    "Unverified",
    "Verified"
};

Ordersheet::Ordersheet( wxWindow* parent, wxWindowID id ) :
    wxGrid( parent, id ) {
    // Set up the ordersheet grid
    CreateGrid( 0, RESERVED_COLUMNS );
    
    // Ordersheet Labels
    SetColLabelValue( 0, "Phone #" );
    SetColLabelValue( 1, "Credit" );
    SetColFormatFloat( 1, 2, 2 );
    AutoSizeColumns( false );
    
    // HACK: Set Phone # Width
    AppendRows();
    SetCellValue( 0, 0, "(555) 555-5555" );
    AutoSizeColumn( 0 );
    SetCellValue( 0, 0, "" );
    DeleteRows( 0 );
}

void Ordersheet::ResetGrid() {
    // Clear products
    while( GetNumberCols() > RESERVED_COLUMNS ) {
        DeleteCols( RESERVED_COLUMNS );
    }
    
    // Clear clients
    while( GetNumberRows() > 0 ) {
        DeleteRows( 0 );
    }
}

void Ordersheet::AddClient( wxString client_name ) {
    // Add the client to the list
    AppendRows();
    SetRowLabelValue( GetNumberRows()-1, client_name );

    // Set up order status
    for( unsigned int i = RESERVED_COLUMNS; i < GetNumberCols(); ++i ) {
        SetCellValue( GetNumberRows()-1, i, STATUS_CHOICES[ 0 ] );
        SetCellEditor( GetNumberRows()-1, i,
                       new wxGridCellChoiceEditor( STATUS_CHOICE_COUNT, STATUS_CHOICES ) );
    }
}

void Ordersheet::AddProduct( wxString product_name ) {
     // Add the product if the name was given
    AppendCols();
    SetColLabelValue( GetNumberCols()-1, product_name );

    // HACK: Cycle through potential order statuses to get a good starting size
    AppendRows();
    SetCellValue( GetNumberRows()-1, GetNumberCols()-1, "UNVERIFIED" );
    AutoSizeColumn( GetNumberCols()-1 );
    DeleteRows( GetNumberRows()-1 );
    
    // Set up order status for new product
    for( int i = 0; i < GetNumberRows(); ++i ) {
        SetCellValue( i, GetNumberCols()-1, STATUS_CHOICES[ 0 ] );
        SetCellEditor( i, GetNumberCols()-1,
                       new wxGridCellChoiceEditor( STATUS_CHOICE_COUNT, STATUS_CHOICES ) );
    }
}

void Ordersheet::OnAddClient( wxCommandEvent& WXUNUSED( event ) ) {
    // Request a client name to add to the list
    wxTextEntryDialog* entry_name = new wxTextEntryDialog( this, "Enter Client Name" );
    if( entry_name->ShowModal() == wxID_OK ) {
        AddClient( entry_name->GetValue() );
    }
}

void Ordersheet::OnRemoveClient( wxCommandEvent& WXUNUSED( event ) ) {
    // Get all selected rows (clients), then sort in reverse order
    wxArrayInt selected_clients = GetSelectedRows();
    selected_clients.Sort( []( int* first, int* second ) {
        return ( *second - *first );
    } );
    
    // Remove clients from bottom to top (to prevent index errors)
    for( unsigned int i = 0; i < selected_clients.GetCount(); ++i ) {
        // Move client names up one row since that is not automatic in wxWidgets
        for( unsigned int j = selected_clients.Item( i )+1; j < GetNumberRows(); ++j ) {
            SetRowLabelValue( j-1, GetRowLabelValue( j ) );
        }
        
        // Now we can delete the rows
        DeleteRows( selected_clients.Item( i ) );
    }
}

void Ordersheet::OnAddProduct( wxCommandEvent& WXUNUSED( event ) ) {
    // Request a product name to add to the list
    wxTextEntryDialog* entry_name = new wxTextEntryDialog( this, "Enter Product Name" );
    if( entry_name->ShowModal() == wxID_OK ) {
        AddProduct( entry_name->GetValue() );
    }
}

void Ordersheet::OnRemoveProduct( wxCommandEvent& WXUNUSED( event ) ) {
    // Get all selected columns (products), then sort in reverse order
    wxArrayInt selected_products = GetSelectedCols();
    selected_products.Sort( []( int* first, int* second ) {
        return ( *second - *first );
    } );
    
    // Remove products from right to left (to prevent index errors)
    for( int i = 0; i < selected_products.GetCount(); ++i ) {
        // Abort if we're in the protected columns (vital client data)
        if( selected_products.Item( i ) < RESERVED_COLUMNS ) {
            break;
        }
        
        // Move product names left one column since that is not automatic in wxWidgets
        for( int j = selected_products.Item( i )+1; j < GetNumberCols(); ++j ) {
            SetColLabelValue( j-1, GetColLabelValue( j ) );
        }
        
        // Now we can delete the columns
        DeleteCols( selected_products.Item( i ) );
    }
}
