echo > ~/.vimrc "
set showmode
set nowrap
set tabstop=4
set softtabstop=4
set expandtab
set shiftwidth=4
set shiftround
set number
set ignorecase
set smartcase
set smarttab
set scrolloff=4
set hlsearch
set incsearch

set nolist
"

export CPPFLAGS='-std=c++11 -DLOCAL -Wall -Wextra -Wconversion -Wshadow -Wno-sign-conversion -D_GLIBCXX_DEBUG -fno-sanitize-recover=undefined -fsanitize=undefined'
