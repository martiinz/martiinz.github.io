---
title: "Ubuntu Desktop Entry"
excerpt: ""
tags:
  - tools
  - linux
categories:
  - linux
---

For the clicky stuff, create a file named `eclipse.desktop` with following content

```ini
[Desktop Entry]
Name=Eclipse
Type=Application
Exec=/opt/eclipse/eclipse
Terminal=false
Icon=/opt/eclipse/icon.xpm
Comment=Integrated Development Environment
NoDisplay=false
Categories=Development;IDE;
Name[en]=Eclipse
Name[en_US]=Eclipse
```

install with

```bash
sudo desktop-file-install eclipse.desktop
```
