valgrind-debug: debug/tp
	valgrind --tool=memcheck --leak-check=full --track-origins=yes --suppressions=make/valgrind-suppressions.txt  --gen-suppressions=no debug/tp $(VALGRIND) 2>&1 

valgrind-release: release/facturation
	valgrind --tool=memcheck --leak-check=full --track-origins=yes --suppressions=make/valgrind-suppressions.txt  --gen-suppressions=no release/tp $(VALGRIND) 2>&1

