<h1 align=center>2048 Game</h1>

<a href="https://www.codefactor.io/repository/github/rahul4732saini/2048"><img src="https://www.codefactor.io/repository/github/rahul4732saini/2048/badge" alt="projectStatus"></a>

<a href="https://www.github.com/rahul4732saini/fise"><img src="https://img.shields.io/badge/status-beta-yellow?maxAge=60" alt="projectStatus"></a>
<a href="https://github.com/rahul4732saini/fise/blob/main/LICENSE"><img src="https://img.shields.io/badge/License-MIT-green?maxAge=60" alt="License"></a>

<a href="https://www.github.com/rahul4732saini/2048"><img src="https://img.shields.io/github/stars/rahul4732saini/2048.svg?style=social&label=Star&maxAge=60" alt="StarProject"></a>
<a href="https://www.twitter.com/rahulsaini4732"><img src="https://img.shields.io/twitter/follow/rahulsaini4732?style=social&label=Follow&maxAge=60" alt="Twitter"></a>
<a href="https://www.linkedin.com/in/rahul4732saini/"><img src="https://img.shields.io/badge/LinkedIn-Connect-blue?style=social&logo=linkedin&maxAge=60" alt="LinkedIn"></a>


<h2 align=center>Description</h2>

The repository offers a TUI-based rendition of the classic **2048** puzzle game, delivering an interactive and engaging experience directly within the command-line interface. This project is designed to provide users with a responsive and intuitive gameplay environment, capturing the essence of the original 2048 puzzle game.​

### Platform Compatibility:

Due to its reliance on the *ncurses* library, this game is primarily compatible with UNIX-based operating systems, such as Linux and MacOS. While Windows does not natively support ncurses, users can still enjoy the game on Windows systems through the Windows Subsystem for Linux (WSL), which provides a UNIX-like environment.

<h2 align=center>Features</h2>

1. **Terminal User Interface (TUI)**: Designed to run entirely within the terminal, this implementation ensures accessibility across various systems without the need for graphical interfaces.​

2. **Responsive Design**: The game adapts dynamically to different terminal sizes, maintaining an optimal layout and user experience regardless of the window dimensions.​

3. **Engaging Gameplay**: Faithfully replicating the original 2048 game mechanics, players combine numbered tiles to reach the elusive 2048 tile, with intuitive controls enhancing the overall experience.

<h2 align=center>Getting Started</h2>

To enjoy this game, follow the steps below to setup and run the game on your local system.

### Prerequisites:

Before installing the game, ensure your system meets the following requirements:

1. **Operating System**: A UNIX-based OS such as Linux or macOS. Windows users can play the game via the Windows Subsystem for Linux (WSL).​

2. **Compiler**: A C compiler like *gcc* is necessary to build the game from source.

3. **ncurses Library**: This library manages the game's Text-based User Interface. Ensure it's installed on your system.

### Installation Options:

You can obtain the game through the following methods:

1. **Cloning the GitHub Repository (Recommended)**:

    This method allows you to access the latest version of the game:

    ```bash
    git clone https://github.com/rahul4732saini/2048.git
    cd 2048
    ```

2. **Downloading the Source Code as a ZIP File**:

    If you prefer not to use `Git`, download the source code directly:

    - Navigate to the repository's main page.​

    - Click on the `Code` button and select `Download ZIP`.​

    - Extract the downloaded ZIP file and navigate to the extracted 2048 directory.​

### Building and Running the Game:

Once you have the source code, compile and run the game with the following steps:

1. **Build the Game**:

    Use the provided `Makefile` to compile the game:

    ```bash
    make
    ```

    This command generates an executable named 2048 in the current directory.

2. **Run the Game**:

    Start the game by executing:

    ```bash
    ./2048
    ```

    The game will launch in your terminal, and you can begin playing immediately.

### Uninstallation:

To remove the game from your system:

1. **Clean Up Build Files**:

    In the game's directory, run:

    ```bash
    make clean
    ```

    This command deletes the executable and any object files generated during compilation.


2. **Remove the Game Directory**:

    Navigate out of the 2048 directory and delete it:

    ```bash
    cd ..
    rm -rf 2048
    ```

    This action removes all game files from your system.

By following these steps, you can set up, enjoy, and, if necessary, effectively remove the terminal-based 2048 game on your UNIX-based system.

## Legals

This project is distributed under the MIT License. Refer to [LICENSE](./LICENSE) for more details.

## Call for Contributions

This project always welcomes your precious expertise and enthusiasm!
The project relies on its community's wisdom and intelligence to investigate bugs and contribute code. We always appreciate improvements and contributions to this project.