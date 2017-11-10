# LaTeX

## Books and manuals
 - [UA] [Не надто короткий вступ до LaTeX 2ε ](https://ctan.org/pkg/lshort-ukr)
 - [RU] [Компьютерная типография LaTeX](https://ctan.org/tex-archive/info/russian/Computer_Typesetting_Using_LaTeX)
 - [RU] [LaTeX2ε в примерах](http://www.ccas.ru/voron/download/voron05latex.pdf)

## Online Help
  - [EN] [TEX StackExchange](https://tex.stackexchange.com/)
  - [EN] [LaTeX Help From ShareLaTeX](https://www.sharelatex.com/learn)
  - [RU] [Сайт M. Балдіна з іншипи посиланнями](https://star.inp.nsk.su/~baldin/LaTeX/index.html)

## Download Distro
  - https://www.latex-project.org/get/
  - https://www.sharelatex.com/


## (my) Editor
[Atom](https://atom.io) з плагінами [language-latex](https://atom.io/packages/language-latex) та [latex-plus](https://atom.io/packages/latex-plus)

![](screen.jpg)

Генерація превю по збереженню файла реалізована через `init.coffee`

```coffeescript
atom.workspace.observeTextEditors (editor) ->
  editor.onDidSave ->
    if 'text.tex.latex' == editor.getGrammar().scopeName.toLowerCase()
      atom.commands.dispatch( atom.views.getView( editor ), 'latex-plus:compile-and-sync' )
```
