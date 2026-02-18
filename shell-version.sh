#!/bin/bash
# git-ignore.sh
# Fügt Dateien zu .gitignore hinzu und entfernt sie aus dem Tracking

if [ "$#" -lt 1 ]; then
  echo "Usage: $0 <file_or_folder> [...]"
  exit 1
fi

# .gitignore existiert nicht? anlegen
[ ! -f .gitignore ] && touch .gitignore

for item in "$@"; do
  # Prüfen, ob schon in .gitignore
  if ! grep -qx "$item" .gitignore; then
    echo "$item" >> .gitignore
    echo "Added '$item' to .gitignore"
  else
    echo "'$item' is already in .gitignore"
  fi

  # Datei/Ordner untracked machen, falls schon getrackt
  if git ls-files --error-unmatch "$item" >/dev/null 2>&1; then
    git rm -r --cached "$item"
    echo "Removed '$item' from git tracking"
  fi
done

