#!/bin/sh

# A simple example of using encoder-decoder

echo -n 'get scoreboard' | ./tr_str.exe -ei | ./send_w.sh | ./tr_str.exe -in
