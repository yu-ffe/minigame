import LoadingScene from "./scene/loading.js";
import MainScene from "./scene/main.js";
import StarterScene from "./scene/starter.js";
import TilemapScene from "./scene/main2.js";

const config = {
    type: Phaser.AUTO,
    width: window.innerWidth, // Set width to window width
    height: window.innerHeight, // Set height to window height
    backgroundColor: 0x999999,
    physics: {
        default: "arcade",
        arcade: {
            gravity: { y: 300 },
            debug: false,
        },
    },
    scene: [LoadingScene, MainScene, StarterScene, TilemapScene],
    tileSize: 32,
    pixelArt: true,
};

// Create the game instance
const game = new Phaser.Game(config);

// Function to toggle fullscreen
function toggleFullScreen() {
    if (!document.fullscreenElement) {
        document.documentElement.requestFullscreen().catch((err) => {
            console.log(`Failed to enter fullscreen mode: ${err.message}`);
        });
    } else {
        if (document.exitFullscreen) {
            document.exitFullscreen().catch((err) => {
                console.log(`Failed to exit fullscreen mode: ${err.message}`);
            });
        }
    }
}

// Listen for a key press or any other event to toggle fullscreen mode
document.addEventListener("keydown", (event) => {
    if (event.code === "F11") {
        // Example: Toggle fullscreen with F11 key
        toggleFullScreen();
    }
});

window.addEventListener("resize", () => {
    game.scale.resize(window.innerWidth, window.innerHeight);
});
