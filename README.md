# Amiget Repository Manager

Amiget is an ecosystem for managing software installations on AmigaOS (and perhaps deratives), loosely inspired by APT found in
Debian and Ubuntu GNU/Linux.

Currently Amiget is in the early design phase. This will be true as long this message remains. However, feel free to contribute with
ideas! You may clone or fork the repository just to play around. Soon enough, there will be a repository launched at amiget.org
and at the same time a very early and feature-incomplete version of the Amiget CLI tool will see daylight.

## Concept

### Repository

* Repositories are hosted on http servers. The official upstream repositories will be hosted on AWS S3, at least for the time being.
* A package is a single file named <filename>-<version>.amg. The amd file is in fact an lha file containing a metadata file named <filename>-<version>.meta and the software files.

### Client

A client is a system where Amiget is installed managing a set of package installations. The software consists of the CLI command `amiget`. Here follows a list of commands. Those with (repo) in desciption need to communicate with a remote repository. All others are working offline towards the local cache.

* `search <keyword>` - search for keyword in package name and description *TODO*
* `show <package>` - show description of given package `<package>` *TODO*
* `install <package>` - (remote) install `<package>` and all its dependencies *TODO*
* `remove <package>` - remove installed `<package>` *TODO*
* `clean-system` - remove packages installed as dependencies if no longer needed *TODO*
* `update` - (remote) update the cache from known repositories *TODO*
* `upgrade [package]` - (remote) update installed packages to latest versions, optionally limited to `[package]` *TODO*
* `list-installed [keyword]` - list installed packages, optionally filtered by `[keyword]` *TODO*
* `package-details <package>` - show details about installed `<package>` *TODO*
* `query-file <file>` - show which package is responsible for a given `<file>`, if any *TODO*
* `export <file>` - export the list of installed packages to given `<file>` *TODO*
* 'import <file>` - (remote) install all packages in given `<file>`, previously exported by `export` *TODO*

## Use Cases

### Search and Install
As a user I want to install a painting program. In a CLI I type `amiget search paint`. I get a list like this:

    deluxepaint_iv 4.0.1
      Widely used 2D painting program with animation features. Demo version.

    personalpaint 3.0.1
      2D painting toolkit with modern interface and good color management.

    gimp 2.8.1
      Free/open source portable painting program usable with high-end Amiga systems.

I am interested in obtaining a copy of Personal Paint. Therefore, I type the command

    amiget install personalpaint

Amiget will now download the personalpaint-3.0.1.lha from the Amiget repository, and after verifying it can be 
safely installed, install it. What safety concerns, it will ensure no existing files will be overwritten and check available
space on the harddrive before unpacking.

### Install dependencies

