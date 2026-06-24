#!/bin/sh
socat tcp-listen:6700,reuseaddr,fork exec:"./chall"