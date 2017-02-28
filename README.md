minishell - TMoska [![Buld Status](https://travis-ci.org/TMoska/minishell.svg)](https://travis-ci.org/TMoska/minishell.svg)
===

Recreation of `/bin/bash` with executable interpretation and some of the builtins.

```
Mandatory part:

1. Prompt, correct error management etc.
2. Interpretor of executables by searching env var PATH.
3. Builtins: echo, cd, setenv, unsetenv, env, exit.

Bonus part:

1. Coloring
2. Termcaps implementation (moving around word, modifying words)
3. HOME & END buttons
4. alt + left/right jumping by words
5. Multi command management by ; separation (cd ; ls)
6. getenv builtin to read ENV var

```

This projects has been a part of curriculum for [42 University](https://www.42.us.org) minishell project.

Usage
---

```
git clone https://github.com/TMoska/minishell.git
cd minishell
make
./minishell
enjoy the shell
```

Studying at 42?
---

You might be interested in checking my other repositories:
- [libft](https://www.github.com/TMoska/libft)
- [sastantua](https://github.com/TMoska/sastantua)
- [42_exams](https://github.com/TMoska/42_exams)
- [fillit](https://github.com/TMoska/fillit)
- [piscine_reloaded](https://github.com/TMoska/piscine_reloaded)

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

