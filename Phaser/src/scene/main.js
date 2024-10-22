export default class MainScene extends Phaser.Scene {
    constructor() {
        super({ key: "MainScene" });
        this.speed = 10; // 이동 속도 설정
        this.gravity = 50; // 중력 설정
        this.velocityY = 0; // 플레이어의 Y 방향 속도
        this.accelerationY = 0; // 중력 가속도
    }

    preload() {
        this.load.bitmapFont("arcade", "/assets/fonts/bitmap/arcade.png", "/assets/fonts/bitmap/arcade.xml");
        this.load.tilemapTiledJSON("map", "/src/resource/tileset/sandbox.json");
        this.load.image("tiles", "/src/resource/tileset/isometric-sandbox-sheet.png");
        this.load.image("player", "/assets/animations/bubble/frame6.png");
        this.load.image("object", "/assets/input/block.png");
        this.load.image("tree", "/assets/demoscene/ball.png");
        this.load.image("grass", "/src/resource/tileset/grass.png");
    }

    create() {
        this.createMap(); // 타일맵 생성
        this.createPlayer(); // 플레이어 생성
        this.createObject(); // 객체 생성
        this.setupCamera(); // 카메라 설정
        this.setupInput(); // 입력 설정
        this.placeTreeOnTile(5, 6); // (5, 6) 위치의 타일 위에 나무 배치
    }

    // Isometric 변환 함수 예제
    isoToScreen(x, y, tileWidth, tileHeight) {
        const screenX = (x - y) * (tileWidth / 2);
        const screenY = (x + y) * (tileHeight / 2);
        return { x: screenX, y: screenY };
    }

    screenToIso(x, y, tileWidth, tileHeight) {
        const isoX = (x / (tileWidth / 2) + y / (tileHeight / 2)) / 2;
        const isoY = (y / (tileHeight / 2) - x / (tileWidth / 2)) / 2;
        return { x: isoX, y: isoY };
    }

    createMap() {
        this.map = this.make.tilemap({ key: "map" });
        let tileset = this.map.addTilesetImage("isometric-sandbox-sheet", "tiles");
        this.layer = this.map.createLayer("Tile Layer 1", tileset);

        this.physics.world.setBounds(0, 0, 1024, 512); // 월드의 경계를 설정
    }
    createPlayer() {
        this.player = this.add.sprite(0, 0, "player");
        this.player.x = this.game.config.width;
        this.player.y = 0;
        this.player.z = this.game.config.height;
        this.player.setOrigin(0.5, 0.5); // 플레이어의 기준점을 중앙으로 설정
        this.player.setDepth(1);
        this.physics.add.existing(this.player);
        this.player.body.setCollideWorldBounds(true);
    }

    createObject() {
        // 객체를 생성하고 중앙으로 설정합니다
        this.interactiveObject = this.add.sprite(500, 400, "object");
        this.interactiveObject.setOrigin(0.5, 0.5); // 객체의 기준점을 중앙으로 설정
    }

    setupCamera() {
        this.cameras.main.flash(1024, 0, 0, 0);
        this.cameras.main.startFollow(this.player, true, 0.1, 0.1);
        this.cameras.main.setZoom(0.35);
    }

    setupInput() {
        this.cursors = this.input.keyboard.createCursorKeys(); // 방향키 입력 설정
        this.spaceBar = this.input.keyboard.addKey(Phaser.Input.Keyboard.KeyCodes.SPACE); // 스페이스바 입력 설정
        this.aKey = this.input.keyboard.addKey(Phaser.Input.Keyboard.KeyCodes.A); // A 키 입력 설정
    }

    update() {
        this.handleMovement(); // 플레이어 이동 처리
        //this.handleGravity(); // 중력/ 처리
        this.checkInteraction(); // 상호작용 체크
        if (this.aKey.isDown) {
            this.handleTileChange(); // 타일 변경 처리
        }
    }

    handleMovement() {
        if (this.cursors.left.isDown) {
            this.movePlayer(-this.speed, 0); // 왼쪽으로 이동
        } else if (this.cursors.right.isDown) {
            this.movePlayer(this.speed, 0); // 오른쪽으로 이동
        }

        if (this.cursors.up.isDown) {
            this.movePlayer(0, -this.speed); // 위쪽으로 이동
        } else if (this.cursors.down.isDown) {
            this.movePlayer(0, this.speed); // 아래쪽으로 이동
        }
    }

    movePlayer(x, y) {
        this.player.x = this.player.x + x;
        this.player.y = this.player.y + y;
    }

    handleGravity() {
        // 플레이어가 위치한 타일의 좌표를 가져옵니다
        const tileX = Math.floor(this.player.x / this.map.tileWidth);
        const tileY = Math.floor(this.player.y / this.map.tileHeight);

        const tile = this.map.getTileAt({ tileX, tileY });
        if (tile) {
            const tileBottomY = (tile.y + 1) * this.map.tileHeight;
            if (this.player.y > tileBottomY) {
                this.player.y = tileBottomY;
                this.velocityY = 0;
            }
        } else {
            // 타일 위에 없을 경우 중력 적용
            this.velocityY += this.gravity * this.getDeltaTime();
            this.player.y += this.velocityY * this.getDeltaTime();
        }
    }

    checkInteraction() {
        if (this.spaceBar.isDown) {
            // 플레이어가 위치한 타일의 좌표를 가져옵니다
            const tileX = Math.floor(this.player.x / this.map.tileWidth);
            const tileY = Math.floor(this.player.y / this.map.tileHeight);

            const tile = this.layer.getTileAt(tileX, tileY);
            if (tile && tile.index === 2) {
                // 타일 ID가 2인 경우 타일을 제거합니다
                this.layer.removeTileAt(tileX, tileY);
                console.log("Tree block interacted with!"); // 상호작용 메시지
            }
        }
    }

    placeTreeOnTile(tileX, tileY) {
        const treeTileID = 2; // 나무의 타일 ID 설정
        const tree = this.add.sprite(
            tileX * this.tileWidth + this.tileWidth / 2, // X 좌표: 타일의 중심
            tileY * this.tileHeight + this.tileHeight / 2, // Y 좌표: 타일의 중심
            "tree"
        );
        tree.setOrigin(0.5, 0.5); // 나무의 기준점을 중앙으로 설정
    }

    getDeltaTime() {
        // 프레임 시간 간격을 초 단위로 반환
        return this.game.loop.delta / 1000;
    }
}
