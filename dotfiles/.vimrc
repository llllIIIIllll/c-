
call plug#begin('~/.vim/plugged')

Plug 'scrooloose/nerdtree', { 'on':  'NERDTreeToggle' }

Plug 'sonph/onehalf', {'rtp': 'vim/'}
Plug 'octol/vim-cpp-enhanced-highlight'
Plug 'terryma/vim-multiple-cursors'
Plug 'kien/ctrlp.vim'

Plug 'haya14busa/incsearch.vim'
Plug 'godlygeek/tabular'

Plug 'Valloric/YouCompleteMe'

Plug 'luochen1990/rainbow'
let g:rainbow_active = 1 "0 if you want to enable it later via :RainbowToggle

call plug#end()

source ~/.config/vim/myvim.vim
source ~/.config/vim/space.vim


# macron
let mapleader = "\<space>"
nnoremap <leader>mm :<c-u><c-r><c-r>='let @'. v:register .' = '. string(getreg(v:register))<cr><c-f><left>
let @q = '0veeebhxJveexr=0j'

