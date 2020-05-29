# Install Ubuntu Desktop Entry

Create file eclipse.desktop with following content

```
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

