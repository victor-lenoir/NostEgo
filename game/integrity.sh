#! /bin/bash

for file in `grep -iR 'new sf::Image' *|cut -d':' -f1`; do
    if ((test `basename "$file"` != "memory_manager.hxx") \
	    && ((test `basename "$file"|cut -d'.' -f2` == "cc") \
		|| (test `basename "$file"|cut -d'.' -f2` == "hxx"))); then
	echo "$file: Image allocated without the memory manager"
    fi
done

for file in `grep -R ' $' *|grep -v matches|cut -d':' -f1`; do
    echo "$file: Trailing whitespace"
done