#!/bin/bash


# Je sais pas coder en bash j'ai fait de mon mieux...
# Merci de votre compréhension bande de bg
# Les Tests sont (selon moi) fonctionnels, hésitez pas si vous voyez des problèmes
# C'est une comparaison directe avec tcsh

# Signé : Quentin Taranne

total_tests=0
passed_tests=0

if [ ! -f "./42sh" ] || [ ! -x "./42sh" ]; then
    echo "Please put mysh in the same directory as the tester."
    exit 1
fi

compare_output() {
    input="$1"
    test_name="$2" 
    echo "### Test: $test_name ###"
    ((total_tests++))
    mysh_output=$(echo "$input" | ./42sh)
    tcsh_output=$(echo "$input" | tcsh)
    if [ "$mysh_output" == "$tcsh_output" ]; then
        ((passed_tests++))
        echo "-------------------------------------"
        echo "Test Passed: $test_name"
        echo "-------------------------------------"
        echo ""
        echo ""
    else
        echo "-------------------------------------"
        echo "Test Failed: $test_name"
        echo "Input: $input"
        echo ""
        echo "mysh Output:"
        echo "$mysh_output"
        echo ""
        echo "tcsh Output:"
        echo "$tcsh_output"
        echo "-------------------------------------"
        echo ""
        echo ""
    fi
}
# test1
compare_output "echo Hello, World!; echo Hello, World!" "Simple command with (point virgule en anglais)"
# test2
compare_output "echo Hello | wc -l" "Pipe between echo and wc -l"
# test3
compare_output "echo Hello; echo World | wc -w" "Multiple commands with (point virgule en anglais) and pipe"
# test4
compare_output "echo Hello, World! > output.txt; cat output.txt" "Redirection (>)"
# test5
compare_output "echo Hello, World! > output.txt; echo Hello again! >> output.txt; cat output.txt" "Redirection append (>>)"
# test6
echo "This is a test file" > input.txt
compare_output "cat < input.txt" "Input redirection (<)"
# test7
compare_output "Vincent jtm" "Non-existent command (Exit 84)"
# test8
compare_output "echo Hello, World! | cat > output.txt; cat output.txt" "Pipe with redirection"
# test9
compare_output "2>&1" "Error redirection (2>&1)"
# test10
compare_output "|" "Only pipe"
#test11
compare_output "ls |" "Invalid pipe"
#test12
compare_output "ls >" "Bad redirect out"
#test13
compare_output "ls > ../testfile ../file" "Ambigous redirect"
#test14
compare_output "ls /bin/?s" "globbings 1"
#test15
compare_output "ls ../src/*.c" "globbings 2"
#test16
compare_output "ls [a-z]*" "globbings 3"
#test17
compare_output "echo 'Hello World !'" "inhibitheur"
#test18
compare_output "which ls" "which"
#test19
compare_output "where ls" "where"
#test20
compare_output "alias toto 'ls -la'; toto'" "alias"
#test21
compare_output "alias toto 'ls -la'; toto'; unalias toto; toto" "inhibitheur"

rm input.txt output.txt testfile 1

echo "### Résultats des tests ###"
echo "$passed_tests sur $total_tests tests réussis."
echo "### j'espère t'as passé tout les tests ###"
