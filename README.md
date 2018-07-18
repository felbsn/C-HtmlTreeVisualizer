# C-HtmlTreeVisualizer
just simple tool that visualize tree structures in c  with using html &amp; javascript


![Demo](https://i.imgur.com/opLTu2v.png)

whole program written in c  and counterpart supported javascript, html, css 

<b> important note:</b> you probably notice that *.cpp filen in project beacause this program
uses CVectorProject source files which depend on 'typename' specifier. Later on i change gcc to msvc 
and i only find a alternative to typename(X)  =>  static_cast<decltype(X)>()

<h1> How To Use </h1>
first you need to give 'data.js' location to program by passing locatioan as a argument
ex:  in shell  
 //i assume you are in windows
myBinary.exe c:/somefile/otherfile/data.js
after running this command you able to enter program and visualize your tree
ofcouse you need to open 'demo.html' file to see what is going on 


shell like (pretty early stuff) own build library help to use commands and action also it is very easy to use 
just is depends on global variables.

