<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Enhanced DVD Game</title>
    <style>
        canvas {
            border: 1px solid #000;
            display: block;
            margin: 20px auto;
        }

        body {
            text-align: center;
        }

        #speedButtons {
            margin-top: 10px;
        }

        button {
            margin: 5px;
            padding: 10px;
            font-size: 16px;
            cursor: pointer;
        }
    </style>
</head>
<body>
    <div id="homeScreen">
        <h1>Choose Ball Speed</h1>
        <div id="speedButtons">
            <button onclick="startGame(1)">Easy</button>
            <button onclick="startGame(2)">Medium</button>
            <button onclick="startGame(3)">Hard</button>
        </div>
    </div>

    <canvas id="gameCanvas" width="800" height="600" style="display: none;"></canvas>

    <script>
        const canvas = document.getElementById("gameCanvas");
        const ctx = canvas.getContext("2d");

        // Paddle properties
        const paddleHeight = 10;
        const paddleWidth = 75;
        let paddleX = (canvas.width - paddleWidth) / 2;

        // DVD symbol properties
        const dvdWidth = 50;
        const dvdHeight = 30;
        let dvdX = canvas.width / 2 - dvdWidth / 2;
        let dvdY = canvas.height / 2 - dvdHeight / 2;
        let dvdSpeedX = 2;
        let dvdSpeedY = 2;

        // Level properties
        let level = 1;
        const maxLevels = 5;

        // Increase difficulty with each level
        function increaseDifficulty() {
            dvdSpeedX += level;
            dvdSpeedY += level;
        }

        // Different backgrounds on failure
        const failureBackgrounds = [
            "#FFD700", // Gold
            "#FF6347", // Tomato
            "#87CEEB", // Sky Blue
            "#98FB98", // Pale Green
            "#FFB6C1", // Light Pink
        ];

        // Handle paddle movement
        function handlePaddleMovement(e) {
            const relativeX = e.clientX - canvas.offsetLeft;
            if (relativeX > 0 && relativeX < canvas.width) {
                paddleX = relativeX - paddleWidth / 2;
            }
        }

        // Event listener for mouse movement
        document.addEventListener("mousemove", handlePaddleMovement);

        // Draw the paddle on the canvas
        function drawPaddle() {
            ctx.beginPath();
            ctx.rect(paddleX, canvas.height - paddleHeight, paddleWidth, paddleHeight);
            ctx.fillStyle = "#0095DD";
            ctx.fill();
            ctx.closePath();
        }

        // Draw the DVD symbol on the canvas
        function drawDVD() {
            ctx.beginPath();
            ctx.rect(dvdX, dvdY, dvdWidth, dvdHeight);
            ctx.fillStyle = `hsl(${Math.random() * 360}, 50%, 50%)`;
            ctx.fill();
            ctx.closePath();
        }

        // Update the game state
        function updateGame() {
            // Move the DVD symbol
            dvdX += dvdSpeedX;
            dvdY += dvdSpeedY;

            // Bounce off the walls
            if (dvdX + dvdSpeedX > canvas.width - dvdWidth || dvdX + dvdSpeedX < 0) {
                dvdSpeedX = -dvdSpeedX;
            }

            if (dvdY + dvdSpeedY > canvas.height - dvdHeight || dvdY + dvdSpeedY < 0) {
                dvdSpeedY = -dvdSpeedY;
            }

            // Check if the DVD symbol hits the paddle
            if (
                dvdY + dvdSpeedY > canvas.height - dvdHeight - paddleHeight &&
                dvdX + dvdSpeedX > paddleX &&
                dvdX + dvdSpeedX < paddleX + paddleWidth
            ) {
                dvdSpeedY = -dvdSpeedY;
            }

            // Level up if the DVD symbol reaches the top
            if (dvdY + dvdSpeedY < 0) {
                level++;
                if (level > maxLevels) {
                    alert("Congratulations! You completed all levels!");
                    document.location.reload();
                } else {
                    alert(`Level ${level}! Get ready for the next challenge!`);
                    resetGame();
                    increaseDifficulty();
                }
            }

            // Different backgrounds on failure
            if (dvdY + dvdSpeedY > canvas.height) {
                const randomBackground =
                    failureBackgrounds[Math.floor(Math.random() * failureBackgrounds.length)];
                canvas.style.backgroundColor = randomBackground;
                setTimeout(() => {
                    canvas.style.backgroundColor = "#fff";
                    alert("Game Over!");
                    document.location.reload();
                }, 1000);
            }
        }

        // Reset the game for a new level
        function resetGame() {
            dvdX = canvas.width / 2 - dvdWidth / 2;
            dvdY = canvas.height / 2 - dvdHeight / 2;
            paddleX = (canvas.width - paddleWidth) / 2;
        }

        // Draw the entire game
        function draw() {
            ctx.clearRect(0, 0, canvas.width, canvas.height); // Clear the canvas
            drawPaddle();
            drawDVD();
            updateGame();
            requestAnimationFrame(draw); // Keep the animation going
        }

        // Start the game with different speeds
        function startGame(speed) {
            document.getElementById("homeScreen").style.display = "none";
            canvas.style.display = "block";
            level = 1;
            dvdSpeedX = speed;
            dvdSpeedY = speed;
            resetGame();
            increaseDifficulty();
            draw();
        }
    </script>
</body>
</html>

