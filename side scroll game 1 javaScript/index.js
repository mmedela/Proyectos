import Sprite from "./classes/sprite.js";

const canvas = document.querySelector('canvas');
const canvasContext = canvas.getContext('2d');

canvas.width = 1024;
canvas.height = 576;

const keys = {
    // LATERAL MOVEMENTS
    a:{
        pressed: false
    },
    d:{
        pressed: false
    },
    ArrowRight:{
        pressed: false
    },
    ArrowLeft:{
        pressed: false
    },
    // VERTICAL MOVEMENTS
    w:{
        pressed: false
    },
    ArrowUp:{
        pressed: false
    }
};

canvasContext.fillRect(0,0, canvas.width, canvas.height);

const player1 = new Sprite({
    position:{
        x:0,
        y:0
    },
    velocity:{
        x:0,
        y:0
    }
});

const player2 = new Sprite({
    position:{
        x:400,
        y:100
    },
    velocity:{
        x:0,
        y:0
    },
    color: 'yellow'
});

function colitionning(p1, p2){
    let a = p1.attackBox.position.x + p1.attackBox.width >= p2.position.x;
    let b = p1.attackBox.position.x <= p2.position.x + p2.width;
    let c = p1.attackBox.position.y + p1.attackBox.height >= p2.position.y;
    let d = p1.attackBox.position.y <= p2.position.y + p2.height;
    return a&&b&&c&&d;
}

function animate(){
    window.requestAnimationFrame(animate);
    canvasContext.fillStyle = 'black';
    canvasContext.fillRect(0,0,canvas.width, canvas.height);
    player1.update(canvasContext, canvas.height);
    player2.update(canvasContext, canvas.height);
    player1.velocity.x = 0;
    player2.velocity.x = 0;
    if(keys.a.pressed && player1.lastKeyPressed == 'a'){
        player1.velocity.x = -5;
    }else if(keys.d.pressed && player1.lastKeyPressed == 'd'){
        player1.velocity.x = 5;
    }

    if(keys.ArrowLeft.pressed && player2.lastKeyPressed == 'ArrowLeft'){
        player2.velocity.x = -5;
    }else if(keys.ArrowRight.pressed && player2.lastKeyPressed == 'ArrowRight'){
        player2.velocity.x = 5;
    }

    if(colitionning(player1, player2) && player1.isAttacking()){
        player1.stopAttack();
        console.log('hola');
    }
}

animate();

window.addEventListener('keydown', (event)=>{
    
    switch(event.key){
        case 'd':
            keys.d.pressed = true;
            player1.lastKeyPressed = 'd';
            break;
        case 'a':
            keys.a.pressed = true;
            player1.lastKeyPressed = 'a';
            break;
        case 'w':
            player1.velocity.y = -20;
            break;
        case ' ':
            player1.attack();
            break;
        case 'ArrowRight':
            keys.ArrowRight.pressed = true;
            player2.lastKeyPressed = 'ArrowRight';
            break;
        case 'ArrowLeft':
            keys.ArrowLeft.pressed = true;
            player2.lastKeyPressed = 'ArrowLeft';
            break;
        case 'ArrowUp':
            player2.velocity.y = -20;
            break;
    }
});

window.addEventListener('keyup', (event)=>{
    
    switch(event.key){
        case 'd':
            keys.d.pressed = false;
            break;
        case 'a':
            keys.a.pressed = false;
            break;
        case 'ArrowRight':
            keys.ArrowRight.pressed = false;
            break;
        case 'ArrowLeft':
            keys.ArrowLeft.pressed = false;
            break;
    }
});