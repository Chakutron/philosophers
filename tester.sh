#!/bin/zsh

echo '\e[91m _____ _   _ _                 _                  _____        _
|  _  | |_|_| |___ ___ ___ ___| |_ ___ ___ ___   |_   _|__ ___| |_ ___ ___
|   __|   | | | . |_ -| . | . |   | -_|  _|_ -|    | || -_|_ -|  _| -_|  _|
|__|  |_|_|_|_|___|___|___|  _|_|_|___|_| |___|    |_||___|___|_| |___|_|
                          |_|                                   by Chaku\e[0m\n'

if [ "$#" -lt 1 ]; then
    echo "Usage: tester.sh <Test Type>"
    echo "\t0: test philo and philo_bonus"
    echo "\t1: test philo only"
    echo "\t2: test philo_bonus only"

    exit
fi

if [ "$1" -gt 2 -o "$1" -lt 0 ]; then
    echo "[Error]: Wrong Arguments"
    exit
fi

echo "\e[92m[+] Test Type: $1\e[0m\n"

error_log ()
{
    echo "[$1-$2]: $3" >> ./errors_log
}

test_one ()
{
	echo "\e[94m[+] Test #1: ./philo 4 310 200 100 during 5 seconds..\e[0m"
    ("./$1" 4 310 200 100 > "./log_$1")&
    sleep 5
    pkill $1
    output=$(grep died -m 1 "./log_$1" | awk '{print $NF}' | cut -c 1-4)
    if [ "$output" = "died" ];then
        echo "\e[92m[+] Test #1 Succeeded !\e[0m"
    else
        echo "\e[91m[+] Test #1 Failed !\e[0m"
		echo "Given 4 310 200 100 arguments to $1, a philosopher should die !"
    fi
    rm -rf "./log_$1"
}

test_two ()
{
    echo "\e[94m[+] Test #2: ./philo 4 410 200 200 during 180 seconds..\e[0m"
    ("./$1" 4 410 200 200 > /dev/null)&
    i=1
    error=0
	while [ $i -lt 180 ];do
        printf "\r[%d...]" $i
        pgrep $1 > /dev/null
        if [ "$?" -ne 0 ];then
            echo "\r\e[91m[+] Test #2 Failed\e[0m"
			echo "Given 4 410 200 200 arguments to $1, NO philosopher should die !"
			error=1
			break
        fi
        sleep 1
        i=$(( $i + 1 ))
    done
    sleep 1
    if [ $error -eq 0 ];then
        pkill $1
        echo "\r\e[92m[+] Test #2 Succeeded\e[0m"
    fi
}

test_three ()
{
    echo "\e[94m[+] Test #3: ./philo 5 800 200 200 during 180 seconds..\e[0m"
    ("./$1" 5 800 200 200 > /dev/null)&
    i=1
    error=0
    while [ $i -lt 180 ];do
        printf "\r[%d...]" $i
        pgrep $1 > /dev/null
        if [ "$?" -ne 0 ];then
            echo "\r\e[91m[+] Test #3 Failed\e[0m"
			echo "Given 4 800 200 200 arguments to $1, no philosopher should die !"
            error=1
            break
        fi
        sleep 1
        i=$(( $i + 1 ))
    done
    sleep 1
    if [ $error -eq 0 ];then
        pkill $1
        echo "\r\e[92m[+] Test #3 Succeeded\e[0m"
    fi
}

test_four ()
{
    ("./$1" 4 410 200 200 $3 > "./log_$1")&
    sleep 10
    pgrep $1 > /dev/null
    if [ "$?" -eq 1 ];then
        lines=$(grep eating "./log_$1" | wc -l)
        if [ $lines -ge $4 ];then
            echo "\t\e[92m[+] Test #4-$5 Succeeded\e[0m"
        else
            echo "\t\e[91m[+] Test #4-$5 Failed\e[0m"
			echo "Given 4 410 200 200 $3 arguments to $1, $1 should only be stopped if each philosopher ate at least $3 times !"
        fi
    else
        echo "\t\e[91m[+] Test #4-$5 Failed\e[0m"
		echo "Given 4 410 200 200 $3 arguments to $1, $1 should stop !"
        pkill $1
    fi
    rm -rf "./log_$1"
}

test_five ()
{
    echo "\e[94m[+] Test #5: ./philo 2 60 60 60..\e[0m"
    i=1
    t=0
    error=0
    while [ $i -le 10 ];do
        ("./$1" 2 60 60 60 > "./log_$1")&
        sleep 2
        pgrep $1 > /dev/null
        if [ "$?" -eq 1 ];then
            printf "\r[%d/10]" $i
			tmp=$(grep died -m 1 "./log_$1" | awk '{print $1}' | sed 's/[^0-9]*//g')
            if [ $i -gt 1 ];then
                x=$(expr $tmp - $t)
                x=${x#-}
                if [ $x -gt 10 ];then
                    printf "\r\e[91m[+] Test #5 Failed\e[0m\n"
					echo "Given 2 60 60 60 arguments to $1, the time difference of each death shouldn't be bigger than 10ms !"
                    error=1
                    break
                fi
            else
                t=$tmp
            fi
        else
            printf "\r\e[91m[+] Test #5 Failed\e[0m\n"
			echo "Given 2 60 60 60 arguments to $1, a philosopher should die !"
            pkill $1
            break
        fi
        i=$(( $i + 1 ))
    done

    if [ $error -eq 0 ];then
        echo "\r\e[92m[+] Test #5 Succeeded\e[0m"
    fi
}

test_six ()
{
    ("./$1" 10 410 200 200 > /dev/null)&
    sleep 2
    forks=$(pgrep $1 | wc -l)
    if [ "$forks" -eq 11 ];then
        printf "\r\e[92m[+] Test #6 Succeeded\e[0m\n"
    else
        printf "\r\e[91m[+] Test #6 Failed\e[0m\n"
		echo "Given 10 410 200 200 arguments to $1, 10 processes should be forked, each process for a philosopher !"
    fi
    pkill $1
}

if [ "$1" -eq 1 -o "$1" -eq 0 ];then
    echo "[============[Testing philo]==============]\n"
    target="philo"
	if [ "$2" -eq 1 -o "$#" -eq 1 ];then
	    test_one $target $1
	    sleep 1
	fi
	if [ "$2" -eq 2 -o "$#" -eq 1 ];then
	    test_two $target $1
	    sleep 1
	fi
	if [ "$2" -eq 3 -o "$#" -eq 1 ];then
    	test_three $target $1
	    sleep 1
	fi
	if [ "$2" -eq 4 -o "$#" -eq 1 ];then
		echo "\e[94m[+] Test #4: ./philo 4 410 200 200 x..\e[0m"
    	test_four $target $1 7 28 1
	    test_four $target $1 10 40 2
    	test_four $target $1 12 48 3
	    test_four $target $1 15 60 4
	    sleep 1
	fi
	if [ "$2" -eq 5 -o "$#" -eq 1 ];then
    	test_five $target $1
	    sleep 1
	fi
    rm -rf "./log_$target"
fi

if [ "$1" -eq 2 -o "$1" -eq 0 ];then
    echo "\n[============[Testing philo_bonus]==============]\n"
    target="philo_bonus"
    test_one $target $1
    test_two $target $1
    test_three $target $1
    echo "\e[94m[+] Test #4 on progress, please wait...\e[0m"
    test_four $target $1 7 28 1
    test_four $target $1 10 40 2
    test_four $target $1 12 48 3
    test_four $target $1 15 60 4
    test_five $target $1
    test_six $target $1
    rm -rf "./log_$target"
fi
