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

#ifndef ORDERSHEET_HPP
#define ORDERSHEET_HPP

#include <wx/grid.h>

class Ordersheet : public wxGrid {
    public:
        Ordersheet( wxWindow* parent, wxWindowID id );
        
        /**
         * Reset the grid to its default state.
         */
        void ResetGrid();
        
        /**
         * Add a client to the sheet.
         * @param client_name The name of the client to add.
         */
        void AddClient( wxString client_name );
        
        /**
         * Add a product to the sheet.
         * @param product_name The name of the product to add.
         */
        void AddProduct( wxString product_name );
        
        void OnAddClient( wxCommandEvent& event );
        void OnRemoveClient( wxCommandEvent& event );
        void OnAddProduct( wxCommandEvent& event );
        void OnRemoveProduct( wxCommandEvent& event );
};

#endif /* ORDERSHEET_HPP */
