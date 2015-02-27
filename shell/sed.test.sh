#!/bin/bash

test_file=sed.test.note

cat >${test_file} <<EOF
hello
world
hello
world
EOF

# sed -i '2i insert' ${test_file}
# sed -i '2a append' ${test_file}
# sed -i '2,3a append2,3' ${test_file}

sed -i '/hello/a\insert' ${test_file}
sed -i '/world/i\insert' ${test_file}
#rm ${test_file}
