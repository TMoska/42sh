minishell / 21sh / 42sh - TMoska, Ede-sous, Ryaoi, Adeletan
===

Recreation of `/bin/bash` with executable interpretation and some of the builtins.

```
Mandatory part:

1. Prompt, correct error management, no leaks, etc ...
2. Interpretor of executables by searching env var PATH.
3. POSIX standard builtins: echo, cd, setenv, unsetenv, env, exit.
4. Termcaps implementation (moving around word, modifying words).
5. HOME, END, ALT + left/right word jumping.
6. Multi command management by separation and operators ( ';', '&&', '||');
7. Input redirections (<);
8. Heredoc (<<);
9. Output redirections (>>, >);
10. Output fd aggregation (1>&2, 2>&-, etc ...);
11. Pipes (|);

Bonus part:

1. Dynamic Auto-completion;
2. Multi Lines management;
3. Completely managed quotes and escaping characters.
4. All history management (!!, !1, !-1, !?param?, !arg, history);

```

This projects has been a part of curriculum for [42 University](https://www.42.us.org) minishell / 21sh / 42sh project.

Usage
---

```
git clone https://github.com/TMoska/minishell.git shell
cd shell
make
./21sh
enjoy the shell
```

Studying at 42?
---

You might be interested in checking my other repositories:
- [sastantua](https://github.com/TMoska/sastantua)
- [42_exams](https://github.com/TMoska/42_exams)
- [piscine_reloaded](https://github.com/TMoska/piscine_reloaded)
- [libft](https://www.github.com/TMoska/libft)
- [fillit](https://github.com/TMoska/fillit)
- [get_next_line](https://github.com/TMoska/get_next_line)
- [ft_ls](https://github.com/TMoska/ft_ls)

Contributing
---

If you feel like contributing or improving some functions, feel free to submit a [Pull Request](https://github.com/TMoska/ft_ls/pulls).

License
---

MIT License

Copyright (c) 2017 Tomas Moška

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
