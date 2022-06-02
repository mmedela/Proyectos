import Sprite from "./classes/sprite.js";

const canvas = document.querySelector('canvas');
const canvasContext = canvas.getContext('2d');

const gravity = 0.2;

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

let lastKeyPressed;

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
    }
});

function animate(){
    window.requestAnimationFrame(animate);
    canvasContext.fillStyle = 'black';
    canvasContext.fillRect(0,0,canvas.width, canvas.height);
    player1.update(canvasContext, canvas.height);
    player2.update(canvasContext, canvas.height);
    player1.velocity.x = 0;
    player2.velocity.x = 0;
    if(keys.a.pressed && player1.lastKeyPressed == 'a'){
        player1.velocity.x = -1;
    }else if(keys.d.pressed && player1.lastKeyPressed == 'd'){
        player1.velocity.x = 1;
    }

    if(keys.ArrowLeft.pressed && player2.lastKeyPressed == 'ArrowLeft'){
        player2.velocity.x = -1;
    }else if(keys.ArrowRight.pressed && player2.lastKeyPressed == 'ArrowRight'){
        player2.velocity.x = 1;
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
            player1.velocity.y = -10;
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
            player2.velocity.y = -10;
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