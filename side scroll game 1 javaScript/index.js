import Sprite from "./classes/sprite.js";

const canvas = document.querySelector('canvas');
const canvasContext = canvas.getContext('2d');

const gravity = 0.2;

canvas.width = 1024;
canvas.height = 576;

const keys = {
    a:{
        pressed: false
    },
    d:{
        pressed: false
    },
    w:{
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
    if(keys.a.pressed && lastKeyPressed == 'a'){
        player1.velocity.x = -1;
    }else if(keys.d.pressed && lastKeyPressed == 'd'){
        player1.velocity.x = 1;
    }
}

animate();

window.addEventListener('keydown', (event)=>{
    
    switch(event.key){
        case 'd':
            keys.d.pressed = true;
            lastKeyPressed = 'd';
            break;
        case 'a':
            keys.a.pressed = true;
            lastKeyPressed = 'a';
            break;
        case 'w':
            player1.velocity.y = -10;
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
    }
});