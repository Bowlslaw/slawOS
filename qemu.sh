#!/bin/sh
set -e
. ./iso.sh

DEBUG='-s -no-reboot -no-shutdown'

qemu-system-$(./target-triplet-to-arch.sh $HOST) -cdrom myos.iso

