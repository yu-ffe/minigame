// LoadingScene.js
export default class LoadingScene extends Phaser.Scene {
  constructor() {
    super({ key: "BootGame" });
  }

  preload() {
    this.load.bitmapFont(
      "arcade",
      "/assets/fonts/bitmap/arcade.png",
      "/assets/fonts/bitmap/arcade.xml"
    );
    this.load.image("background", "/assets/skies/background1.png");
    this.load.on("complete", this.onLoadComplete, this);
  }

  create() {
    this.add
      .image(0, 0, "background")
      .setOrigin(0, 0)
      .setDisplaySize(this.cameras.main.width, this.cameras.main.height);

    const { width, height } = this.cameras.main;
    const centerX = width / 2;
    const centerY = height / 2;

    this.loadingText = this.add
      .bitmapText(centerX, centerY, "arcade", "Loading", 32)
      .setOrigin(0.5, 0.5);

    this.dotCount = 0;

    this.time.addEvent({
      delay: 393,
      callback: this.updateLoadingText,
      callbackScope: this,
      loop: true,
    });
  }

  updateLoadingText() {
    this.dotCount = (this.dotCount % 3) + 1;
    let dots = ".".repeat(this.dotCount);
    this.loadingText.setText("Loading" + dots);
  }

  onLoadComplete() {
    this.scene.start("StarterScene");
  }
}
