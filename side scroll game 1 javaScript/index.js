import Sprite from "./classes/sprite.js";

const canvas = document.querySelector('canvas');
const canvasContext = canvas.getContext('2d');

const gravity = 0.2;

canvas.width = 1024;
canvas.height = 576;

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
}

animate();