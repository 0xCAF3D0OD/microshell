echo ./microshell /bin/ls "|" /bin/cat -n
./microshell /bin/ls "|" /bin/cat -n

exit
echo ./microshell /bin/ls "|" /bin/cat -n Makefile
./microshell /bin/ls "|" /bin/cat -n Makefile

echo ./microshell /bin/ls ";" /bin/cat -n Makefile
./microshell /bin/ls ";" /bin/cat -n Makefile

echo ./microshell cd srcs ";" /bin/ls -l
./microshell cd srcs ";" /bin/ls -l

echo ./microshell cd asdf ";" /bin/ls -l
./microshell cd asdf ";" /bin/ls -l

echo ./microshell cd srcs extra ";" /bin/ls -l
./microshell cd srcs extra ";" /bin/ls -l

echo ./microshell cd  ";" /bin/ls -l
./microshell cd  ";" /bin/ls -l

echo ./microshell ls -la
./microshell ls -la

echo ./microshell /bin/ls -la ";" /bin/cat -n Makefile
./microshell /bin/ls -la ";" /bin/cat -n Makefile

echo ./microshell
./microshell

echo ./microshell ls
./microshell ls

echo ./microshell ls -la
./microshell ls -la

echo ./microshell ls -la ";" cat -n
./microshell ls -la ";" cat -n
