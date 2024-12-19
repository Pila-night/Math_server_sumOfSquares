#!/bin/bash


read -p "Введите количество процессов для запуска: " NUM_PROCESSES

for i in {1..10}; do ./client_int32_t -H SHA224 -S s & done; wait
echo "Все процессы завершены."
