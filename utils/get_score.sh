#!/bin/sh

# A simple example of using encoder-decoder

echo -n 'get scoreboard' | ./tr_str -ei | ../icfpc2024/utils/send.sh | ./tr_str -in
