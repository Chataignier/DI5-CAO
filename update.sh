#!/bin/bash

endScriptError() {
    kdialog --title "Error" --error "An error occurred. See the console for details"
    qdbus $dbusRef close 2> /dev/null > /dev/null
    exit 1
}


[[ -z $(which kdialog) ]] && "kdialog not found." && exit 1
[[ -z $(which wget) ]] && "wget not found." && exit 1

wget -q -O - https://storage.projectsforge.org/update/algograph/update.sh > update.sh-new
if (diff update.sh update.sh-new >/dev/null 2>/dev/null) ; then
  echo "Script is up to date. Continuing..."
  rm update.sh-new
else
  mv update.sh-new update.sh
  chmod +x update.sh
  echo "Script updated to latest version. Restarting..."
  bash -c ./update.sh
  exit $?
fi


kdialog --title "Did you backup yours files before this operation ?" --yesno "Did you backup yours files before this operation ?"
if [[ "$?" = "1" ]]; then
    exit 1
fi

dbusRef=$(kdialog --title "Downloading files..." --progressbar "Self updating...                                                                                       " 4)

arch=$(uname -m)

rm -rf update
mkdir -p update

qdbus $dbusRef setLabelText "Downloading files..." 2> /dev/null > /dev/null



qdbus $dbusRef Set "" value 1 2> /dev/null > /dev/null
wget -q --no-check-certificate https://storage.projectsforge.org/update/algograph/base-$arch.tar.gz -O update/base.tar.gz || endScriptError
qdbus $dbusRef Set "" value 2 2> /dev/null > /dev/null
wget -q --no-check-certificate https://storage.projectsforge.org/update/algograph/doc.tar.gz -O update/doc.tar.gz || endScriptError
qdbus $dbusRef Set "" value 3 2> /dev/null > /dev/null
wget -q --no-check-certificate https://storage.projectsforge.org/update/algograph/user-$arch.tar.gz -O update/user.tar.gz || endScriptError

qdbus $dbusRef setLabelText "Extracting files..." 2> /dev/null > /dev/null
qdbus $dbusRef Set "" value 4 2> /dev/null > /dev/null
tar -xzf update/base.tar.gz || endScriptError
tar -xzf update/doc.tar.gz || endScriptError
tar -xzkf update/user.tar.gz # || endScriptError

rm -rf update

qdbus $dbusRef close 2> /dev/null > /dev/null

exit 0