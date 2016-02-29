#!/bin/sh

# 获取当前脚本的路径, 并加入到PATH环境变量中
WORKDIR=`dirname $0`
export PATH=$PATH:$WORKDIR

TMPFILE=/tmp/a.txt
SORTED_FILE=sort.txt
OUTER_SORT_FILE=multiple_merge.txt
OUTER_SORT_OPT_FILE=multiple_merge_opt.txt
SEQ_PREFIX=seq_

# 生成1000个随机数
gen_random.sh 1000 > $TMPFILE

# 将1000个随机数分割成5个文件
split -200 -a1 --additional-suffix=.txt $TMPFILE $SEQ_PREFIX

# 将每个文件排序
SEQ_FILES=`ls $SEQ_PREFIX*`
for file in $SEQ_FILES
do
	sort -n $file -o $file.tmp
	mv $file.tmp $file
done

test_multiple_merge $SEQ_FILES -o $OUTER_SORT_FILE
test_multiple_merge_opt $SEQ_FILES -o $OUTER_SORT_OPT_FILE

# 排序1000个随机数
cat $TMPFILE | sort -n > $SORTED_FILE

