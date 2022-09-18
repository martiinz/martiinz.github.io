---
title: "Git Cheat sheet"
excerpt: ""
tags:
  - git
  - tools
categories:
  - tools
---

## basic branching

### create branch

```bash
git co -b <BRANCH>

# or explicit
git branch <BRANCH>
git co <BRANCH>
```

### push new branch

```bash
git push --set-upstream origin <BRANCH>
```

### basic merging

```bash
git co master 
git merge <BRANCH>
```

### delete branch

```bash
# locally (use -D to force)
git branch -d <BRANCH>

# remotely
git push origin --delete <BRANCH>

# list all, local refences and remote tracking
# branches that you deleted over github webinterface, will still exist locally
git branch -a

# clean up local tracking branches
git fetch --prune origin
```

## file permission

```bash
# show file permission
git ls-files --stage

# make file executable
git update-index --chmod=+x foo.sh
```

## add remote repo

In case I want to push an existing (local) repo to github

- create new github repo
- add as remote locally
- push to remote

```bash
# add a new remote origin
git remote add origin git@github.com:username/my-new-project.git
# push 
# -u will set origin as default
# -f forces to overwite remote repo
git push -u -f origin master
```

In case I want to merge from "master fork"

```bash
git remote add <shortname> git://github.com/<owner>/<repo>.git
git pull <shortname> <branch>
```

## add something to a commit

In case you missed some lines or want to change you're commit message

```bash
# add you're additional changes (or not for only commit message change)
git add <myfile>

# use the --amend, --no-edit for no change on commit message
git commit --amend

# push, you need to use -f for push to remote
# never push to a public branch, you're teammates will love you
git push -f origin <branch>
```
