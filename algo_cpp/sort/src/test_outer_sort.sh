#!/bin/sh

# 获取当前脚本的路径, 并加入到PATH环境变量中
WORKDIR=`dirname $0`
export PATH=$PATH:$WORKDIR

RANDOM_FILE=/tmp/a.txt
SORTED_FILE=/tmp/sort.txt
OUTER_SORT_FILE=/tmp/outer_sort.txt
OUTER_SORT_OPT_FILE=/tmp/outer_sort_opt.txt

# 生成1000个随机数
gen_random.sh 40000 > $RANDOM_FILE

test_outer_sort $RANDOM_FILE $OUTER_SORT_FILE
test_outer_sort_opt $RANDOM_FILE $OUTER_SORT_OPT_FILE

# 排序1000个随机数
cat $RANDOM_FILE | sort -n > $SORTED_FILE

