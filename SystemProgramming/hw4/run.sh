# !bin/bash

if [ $# -eq 0 ]
then
	make DEBUG=0
elif [ $# -eq 1 -a "$1" = "-d" ]
then
	make DEBUG=1
else
	echo "Usage: ./run.sh [-d]"
	exit 1
fi

if [ ! -s test_label.csv ]
then
	./prepare_data
fi

echo "Regular:"
time ./hw4 data/X_train data/y_train data/X_test 100
python validate.py
echo ""

echo "Bonus:"
time ./bonus data/X_train data/y_train data/X_test 32 100
python validate.py
echo ""

echo "Bonus (static link):"
time ./bonus_static_link data/X_train data/y_train data/X_test 32 100
python validate.py
echo ""

export LD_LIBRARY_PATH=.
echo "Bonus (dynamic link):"
time ./bonus_dynamic_link data/X_train data/y_train data/X_test 32 100
python validate.py