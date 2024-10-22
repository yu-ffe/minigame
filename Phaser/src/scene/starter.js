export default class StarterScene extends Phaser.Scene {
    constructor() {
        super({ key: "StarterScene" });
    }

    preload() {
        this.load.image("logo", "/assets/logo.png");
        this.load.image("startButton", "/assets/startButton.png");
    }

    create() {
        const { width, height } = this.cameras.main;
        const centerX = width / 2;
        const centerY = height / 2;
        this.logo = this.add.image(centerX, centerY, "logo");
        this.startButton = this.add.sprite(centerX, centerY - 100, "startButton").setInteractive();

        this.loadingText = this.add.bitmapText(centerX, centerY, "arcade", "click to F11", 32).setOrigin(0.5, 0.5);

        this.startButton.on("pointerdown", () => {
            this.startGame();
        });

        // 스페이스바 입력 설정
        this.spaceBar = this.input.keyboard.addKey(Phaser.Input.Keyboard.KeyCodes.SPACE);
    }

    update() {
        // 스페이스바 입력 체크
        if (this.spaceBar.isDown) {
            this.startGame();
        }
        this.startGame();
    }

    startGame() {
        const delay = 0;
        //const delay = 500;///

        this.tweens.add({
            targets: this.startButton,
            alpha: 0,
            duration: delay,
            ease: "Power1",
            onComplete: () => {
                this.startButton.destroy();
            },
        });

        setTimeout(() => {
            this.scene.start("TilemapScene");
        }, delay);
    }
}
