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

#ifndef APP_HPP
#define APP_HPP

#include <wx/wx.h>
#include "Ordersheet.hpp"

class App : public wxApp {
    private:
        wxString current_filename;
        
        Ordersheet* ordersheet;
        
        void SetupWidgets();
        void SetupOrdersheet( wxFrame* window, wxBoxSizer* sizer );
        void SetupButtons( wxFrame* window, wxBoxSizer* sizer );
        void SetupMenu( wxFrame* window );
        
        bool PickFilenameOpen();
        bool PickFilenameSave();
        void OpenFromFile( wxString& filename );
        void SaveToFile( wxString& filename );
        
    public:
        virtual bool OnInit();
        
        void OnFileNew( wxCommandEvent& event );
        void OnFileOpen( wxCommandEvent& event );
        void OnFileSave( wxCommandEvent& event );
        void OnFileSaveAs( wxCommandEvent& event );
};

#endif /* APP_HPP */
