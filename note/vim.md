1.  跨vim复制的方法：选中要复制的行，然后按"+y,移到另外一个vim,按"+p就ok了
2. vim粘贴代码全乱的解决方法：设置:set paste，进入复制模式,复制完成后:set nopaste,可以设置快捷键map <F2> :set pastetoggle<CR>
3. 大小写转换： gu, gU
        ggguG: 全文转小写       gggUG: 全文转大写
        guw 、gue:  将某个单词转小写
        gUw 、gUe： 将某个单词转大写
        gu5w、gu5e:  转换5个单词
        gU5w、gU5e
        gU0        ：从光标所在位置到行首，都变为大写
        gU$        ：从光标所在位置到行尾，都变为大写
        gUG        ：从光标所在位置到文章最后一个字符，都变为大写
        gU1G      ：从光标所在位置到文章第一个字符，都变为大写


1. Session操作
    - :mks[!] [file] 把当前视图保存到file,如file未指定,则缺省为Session.vim
    - vim -S Session.vim 打开Session.vim,也就是Reload view,重新打开视图
    - [reference](http://feeds.feedburner.com/godorz/arthur1989#kmemcacheE)
2. 对齐文本::[range] Tabluarize /{char1}, 如:121,143 Tabluarize /= 按照等好对其
3. 所谓宏,就是一段录制好的操作.
    - q${register}<commands>q 录制commands到寄存器register
    - [N]@register 重放寄存器register中的宏N次
4. df=, yf=, cf=, vf= 从当前字符开始删除(复制,改变,选中),直到遇到=之后, dt”, yt”, ct”, vt” 从当前字符开始删除(复制,改变,选中),直到遇到”之前
