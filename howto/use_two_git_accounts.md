#  Two Github accounts on same machine

```bash
# create additional ssh key
ssh-keygen -t rsa -C "work@example.com" -f ~/.ssh/id_rsa_work

# add public key to your Github account
# under Settings -> SSH -> New SHH Key

# register the new key with the ssh agent
ssh-add ~/.ssh/id_rsa__work

# create config file, config as follows
# replace hostname and keyfile in second account
vim ~./ssh/config

	# default
    Host github.com
       HostName github.com
       User git
       IdentityFile ~/.ssh/id_rsa

    # work 
    Host github-work   
       HostName github.com
       User git
       IdentityFile ~/.ssh/id_rsa_work
       
# clone repo
git clone <url>

# dont forget to set username, mail
git config user.name "workname"
git config user.email "work@example.com"

```

