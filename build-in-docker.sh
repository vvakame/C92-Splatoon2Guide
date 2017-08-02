#!/bin/bash -eux

docker run -t --rm \
  -v $(pwd):/book vvakame/review@sha256:dd4dcf3e5e4b2b317915bc5e1b4e07024ebc48129693c7eb675073ad86b70454 \
  /bin/bash -ci "cd /book && ./setup.sh && npm run pdf && ./grayscale.sh"
