<div align="center">
    <h1>
        minishell
    </h1>
    <h4>An attempt to implement part of the shell functionality</h4>
    <p>
        <a href="#Description">Description</a> •
        <a href="#Compile">Compile</a> •
        <a href="#Use">Use</a> •
        <a href="https://github.com/blazeitdude/libft/blob/master/LICENSE">License</a>
    </p>
</div>


>**important!**  Attention! to work correctly, you will need the installed GNU readline library.<br/>
> I posted the current version of the library at the time of the first push, but if you have a Mac, you can install it via Homebrew
> to enable your library, if you don't have Homebrew installed, change the **appropriate flags in the Makefile**

<p align="center">
  <img src="https://i.imgur.com/elwDVlr.png" width="100%" />
</p>

## Description
<h4>• this project is able to run binary files both on an absolute path or on the path of the PATH variable</h4>
<h4>• single and double quotes are handled correctly, including with environment variables</h4>
<h4>• some built-in functions have been rewritten</h4>
<h4>• the user name and shell level are determined (incremented)</h4>
<h4>• redefined behavior of signals such as CTR+C CTR+\ CTR+D</h4>

## Compile
to build a project<br/>
`$ make`<br/>
to delete %.o files<br/>
`$ make clean`<br/>
to delete %.o and the library<br/>
`$ make fclean`<br/>
to rebuild the project<br/>
`$ make re`<br/>
## Use

```
.
├── Makefile     --> Building a project
├── README.md
├── includes     --> header files
├── libft        --> libft library see ldione/libft
├── readline-8.2 --> GNU Readline Library
└── sources      --> source code files
```