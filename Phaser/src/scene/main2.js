export default class TilemapScene extends Phaser.Scene {
    constructor() {
        super({ key: "TilemapScene" });
    }

    preload() {
        // Load the tileset image and tilemap data
        this.load.image("tiles", "/src/resource/tileset/isometric-sandbox-sheet.png"); // 타일셋 이미지 경로
        this.load.tilemapTiledJSON("map", "/src/resource/tileset/sandbox.json"); // 타일맵 JSON 경로
        this.load.image("player1", "/src/resource/tileset/man.png"); // 플레이어 스프라이트 경로
    }

    create() {
        // 타일맵 로드 및 아이소메트릭 레이어 생성
        const map = this.add.tilemap("map");
        const tileset = map.addTilesetImage("isometric-sandbox-sheet", "tiles");

        // 아이소메트릭 레이어 설정
        this.layer = map.createLayer("Tile Layer 1", tileset);
        this.layer.setCollisionByProperty({ collides: true });
        console.log(this.layer.x + " " + this.layer.y);
        console.log(this.layer.width + " " + this.layer.height);

        // 플레이어 생성
        this.player1 = this.physics.add.sprite(100, 100, "player1");
        this.player1.setCollideWorldBounds(true);

        // 플레이어 속성 설정
        this.playerSpeed = 160;
        this.player1.setDrag(1000); // Apply friction for smoother stopping
        this.player1.setMaxVelocity(this.playerSpeed);

        // 카메라 설정
        this.cameras.main.startFollow(this.player1);
        this.cameras.main.setBounds(0, 0, this.layer.width, this.layer.height);

        // 입력 설정
        this.cursors = this.input.keyboard.createCursorKeys();
    }

    update() {
        // 플레이어와 레이어와의 충돌
        this.physics.collide(this.player1, this.layer);

        // 플레이어 이동
        this.player1.setVelocity(0);

        if (this.cursors.left.isDown) {
            this.player1.setVelocityX(-this.playerSpeed);
        } else if (this.cursors.right.isDown) {
            this.player1.setVelocityX(this.playerSpeed);
        }

        if (this.cursors.up.isDown) {
            this.player1.setVelocityY(-this.playerSpeed);
        } else if (this.cursors.down.isDown) {
            this.player1.setVelocityY(this.playerSpeed);
        }
        if (this.cursors.space.isDown) {
            const tileX = Math.floor(this.player1.x);
            const tileY = Math.floor(this.player1.y);
            console.log(tileX + " " + tileY);
            // 타일 정보를 가져옵니다
            const tile = this.layer.getTileAt(tileX, tileY);
            console.log(tile);
            console.log(this.layer.getTileAtWorldXY(tileX, tileY));
        }

        // 플레이어가 타일 위에 서 있는지 확인
        this.checkTileUnderPlayer();
    }

    checkTileUnderPlayer() {
        // 현재 플레이어 위치에 있는 타일의 좌표 계산
        const tileX = Math.floor(this.player1.x);
        const tileY = Math.floor(this.player1.y);
    }
}
