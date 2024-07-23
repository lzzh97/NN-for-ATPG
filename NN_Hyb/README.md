# atpg-based-on-atalanta

## Overview
The atalanta readme is located at [link](https://github.com/ONQLin/atpg-based-on-atalanta/blob/master/README_atlanta)

## Action Item
- 2022/12/31: Now it will update decision tree info to "./1atpg_db.txt". It contains gates info each line and partioned by log"!!!update ...". And
each fault is partioned by log"----update fan...". If you want to get the current decision, just refer to the last line of each decision
Remember that every time run the ATPG, it will renew the file now.

- 2023/1/3: In "./1atpg_db.txt", the running output will be recorded. "backtrace" is followed by one or more "assignment". For a "backtrace", if the second following "assignment" is followed "backtrack", or the "assignment" is empty, the all gates in the "backtrace" should be labeled as 0.

- 2023/1/3: In parameters folder, now it can auto gen model cpp by model2cpp.py. It now relies on the weights files model_xxx.txt and mannually inserting the NN's structure with lists. Next plan to load json to check and integrate the org of NN automatically(filling the lists).

## Progress
1. identiy backtrace results. Everytime a decision is made during backtrace, if it gets a PI assignment, label this decision as 1, otherwise it's 0.
2. Record decision parameters, such as gate type, controlability, line value and so on.
