---
title: "Setup Jekyll"
excerpt: "quick local setup"
tags:
  - tools
categories:
  - tools
---

## build and run page

```bash
# cd to page folder
bundle exec jekyll serve --livereload
```

browse [http://localhost:4000](http://localhost:4000)

## setup jekyll and page

Install Ruby, RubyGems, GCC and make (see [installation](https://jekyllrb.com/docs/installation/))

```bash
sudo apt-get install ruby-full build-essential zlib1g-dev

# check
ruby -v 
gem -v
gcc -v
g++ -v
make -v
```

Install jekyll and its stuff (see [quickstart](https://jekyllrb.com/docs/#instructions))

do not run gem as sudo it will mess up you installation (see [ubuntu guide](https://jekyllrb.com/docs/installation/ubuntu/))

```bash
gem install jekyll bundler
bundle add webrick # ruby 3.0.0 and above
```

setup page

```bash
jekyll new myblog
```

Yess! Ready to turn you're markdown notes into a shiny webpage.
