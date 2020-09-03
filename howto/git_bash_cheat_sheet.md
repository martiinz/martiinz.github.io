# basic branching

## create branch

```bash
git co -b <BRANCH>

# or explicit
git branch <BRANCH>
git co <BRANCH>
```

## push new branch 
```bash
git push --set-upstream origin <BRANCH>
```

## basic merging
```bash
git co master 
git merge <BRANCH>
```

## delete branch 
```bash
# locally (use -D to force)
git branch -d <BRANCH>

# remotely
git push origin --delete <BRANCH>
```
