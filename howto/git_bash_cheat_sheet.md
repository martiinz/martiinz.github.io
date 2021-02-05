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
```

## file permission
```bash
# show file permission $
git ls-files --stage

# make file executable
git update-index --chmod=+x foo.sh
```

## remote repo
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
