
const nivel = document.getElementById("nivel");
const botaoIniciar = document.getElementById("iniciar");
const jogo = document.getElementById("jogo");

const ordemNiveis = ["facil", "medio", "dificil"];
let indiceNivelAtual = 0;

const niveis = {
    facil: {
        nome: "Fácil",
        tamanho: 8,
        palavras: ["CPU", "RAM", "KERNEL", "SISTEMA"],
        texto: "O SISTEMA operacional gerencia o computador. O KERNEL controla recursos importantes. A CPU processa instruções e a RAM guarda dados temporários."
    },

    medio: {
        nome: "Médio",
        tamanho: 12,
        palavras: [
            "PROCESSO", "MEMORIA", "ARQUIVO",
            "DRIVER", "NUCLEO", "USUARIO"
        ],
        texto: "O USUARIO utiliza o sistema operacional para executar cada PROCESSO. A MEMORIA guarda dados, o ARQUIVO organiza informações, o DRIVER permite a comunicação com dispositivos e o NUCLEO coordena as operações."
    },

    dificil: {
        nome: "Difícil",
        tamanho: 15,
        palavras: [
            "ESCALONAMENTO", "PROCESSADOR", "SEGURANCA",
            "MULTITAREFA", "MEMORIA", "ARQUIVO", "PROCESSO"
        ],
        texto: "O ESCALONAMENTO organiza os processos para o PROCESSADOR. A MULTITAREFA permite executar várias atividades. A MEMORIA armazena dados, o ARQUIVO guarda informações e a SEGURANCA ajuda a proteger o sistema."
    }
};

let grade = [];
let palavras = [];
let encontradas = [];
let primeira = null;
let transicaoPendente = false;

const direcoes = [
    [-1, -1], [-1, 0], [-1, 1],
    [0, -1],             [0, 1],
    [1, -1],  [1, 0],    [1, 1]
];

function criarGrade(tamanho) {
    return Array.from(
        { length: tamanho },
        () => Array(tamanho).fill("")
    );
}

function inserirPalavra(palavra) {
    const n = grade.length;

    for (let tentativa = 0; tentativa < 5000; tentativa++) {
        const linha = Math.floor(Math.random() * n);
        const coluna = Math.floor(Math.random() * n);

        const [dl, dc] =
            direcoes[Math.floor(Math.random() * direcoes.length)];

        const posicoes = [];
        let pode = true;

        for (let i = 0; i < palavra.length; i++) {
            const l = linha + i * dl;
            const c = coluna + i * dc;

            if (
                l < 0 || l >= n ||
                c < 0 || c >= n ||
                (grade[l][c] !== "" && grade[l][c] !== palavra[i])
            ) {
                pode = false;
                break;
            }

            posicoes.push([l, c]);
        }

        if (pode) {
            posicoes.forEach(([l, c], i) => {
                grade[l][c] = palavra[i];
            });

            return true;
        }
    }

    return false;
}

function prepararJogo(escolhido) {
    const config = niveis[escolhido];

    transicaoPendente = false;
    primeira = null;
    encontradas = [];
    palavras = [...config.palavras];

    for (let rodada = 0; rodada < 100; rodada++) {
        grade = criarGrade(config.tamanho);

        if (palavras.every(inserirPalavra)) {
            for (let l = 0; l < grade.length; l++) {
                for (let c = 0; c < grade.length; c++) {
                    if (grade[l][c] === "") {
                        grade[l][c] = String.fromCharCode(
                            65 + Math.floor(Math.random() * 26)
                        );
                    }
                }
            }

            mostrarJogo(escolhido);
            return;
        }
    }

    jogo.textContent =
        "Não foi possível montar a grade. Clique em Iniciar para tentar novamente.";
}

function mostrarJogo(escolhido) {
    const config = niveis[escolhido];
    const numeroNivel = indiceNivelAtual + 1;

    jogo.innerHTML = `
        <h2>Nível ${numeroNivel} - ${config.nome}</h2>

        <h3>📖 Texto de apoio</h3>
        <p style="
            line-height:1.7;
            padding:12px;
            border-radius:8px;
            background:#f0f4f8;
            color:#222;
        ">${config.texto}</p>

        <p>Leia o texto e encontre todas as palavras escondidas.
        Clique na primeira e na última letra de cada palavra.</p>

        <p id="mensagem" aria-live="polite">
            Clique na primeira letra de uma palavra.
        </p>

        <div id="grade" style="
            display:grid;
            grid-template-columns:repeat(${grade.length}, minmax(0, 1fr));
            gap:3px;
            width:100%;
            max-width:650px;
            margin:15px 0;
        "></div>

        <h3>Palavras para encontrar</h3>
        <ul id="lista-palavras"></ul>
        <p id="pontuacao"></p>
    `;

    const gradeHTML = document.getElementById("grade");

    grade.forEach((linha, l) => {
        linha.forEach((letra, c) => {
            const celula = document.createElement("button");

            celula.textContent = letra;
            celula.dataset.linha = l;
            celula.dataset.coluna = c;

            celula.style.cssText = `
                padding:6px 0;
                min-width:0;
                font-weight:bold;
                font-size:clamp(10px, 2vw, 16px);
                cursor:pointer;
                border:1px solid #999;
                border-radius:4px;
                background:white;
                color:#222;
            `;

            celula.addEventListener("click", () => {
                if (!transicaoPendente) {
                    selecionar(l, c);
                }
            });

            gradeHTML.appendChild(celula);
        });
    });

    atualizarPalavras();
}

function atualizarPalavras() {
    const lista = document.getElementById("lista-palavras");

    lista.innerHTML = palavras.map(palavra => `
        <li style="${
            encontradas.includes(palavra)
                ? "color:green;text-decoration:line-through;"
                : ""
        }">
            ${encontradas.includes(palavra) ? "✓" : "○"} ${palavra}
        </li>
    `).join("");

    document.getElementById("pontuacao").textContent =
        `Pontuação: ${encontradas.length} de ${palavras.length}`;

    if (
        encontradas.length === palavras.length &&
        !transicaoPendente
    ) {
        concluirNivel();
    }
}

function concluirNivel() {
    transicaoPendente = true;

    const mensagem = document.getElementById("mensagem");

    if (indiceNivelAtual < ordemNiveis.length - 1) {
        mensagem.textContent =
            "Parabéns! Você completou o nível! Preparando o próximo...";

        setTimeout(() => {
            indiceNivelAtual++;

            prepararJogo(ordemNiveis[indiceNivelAtual]);

            window.scrollTo({
                top: 0,
                behavior: "smooth"
            });
        }, 1800);

    } else {
        jogo.innerHTML = `
            <div style="
                text-align:center;
                padding:25px 12px;
                border-radius:12px;
                background:#e8f5e9;
                color:#1b5e20;
            ">
                <h2>🎉 PARABÉNS, VOCÊ É FERA! 🎉</h2>
                <p>Você completou os três níveis do caça-palavras!</p>
                <p>Você mostrou que entende de Sistemas Operacionais!</p>
                <button id="jogarNovamente" style="
                    padding:12px 20px;
                    border:0;
                    border-radius:8px;
                    cursor:pointer;
                    font-weight:bold;
                ">Jogar novamente</button>
            </div>
        `;

        document.getElementById("jogarNovamente")
            .addEventListener("click", iniciarSequencia);
    }
}

function selecionar(l, c) {
    const mensagem = document.getElementById("mensagem");

    if (!primeira) {
        primeira = [l, c];

        mensagem.textContent =
            "Agora clique na última letra da palavra.";

        pintarSelecao();
        return;
    }

    const segunda = [l, c];

    verificarPalavra(primeira, segunda);

    primeira = null;
    pintarSelecao();
}

function verificarPalavra(inicio, fim) {
    const [l1, c1] = inicio;
    const [l2, c2] = fim;

    const dl = l2 - l1;
    const dc = c2 - c1;

    if (dl !== 0 && dc !== 0 && Math.abs(dl) !== Math.abs(dc)) {
        document.getElementById("mensagem").textContent =
            "A seleção precisa ser reta ou diagonal.";
        return;
    }

    const passos = Math.max(Math.abs(dl), Math.abs(dc)) + 1;
    const passoL = Math.sign(dl);
    const passoC = Math.sign(dc);

    const palavra = Array.from({ length: passos }, (_, i) =>
        grade[l1 + i * passoL][c1 + i * passoC]
    ).join("");

    const invertida = palavra.split("").reverse().join("");

    const encontrada = palavras.find(p =>
        !encontradas.includes(p) &&
        (p === palavra || p === invertida)
    );

    if (encontrada) {
        encontradas.push(encontrada);

        document.getElementById("mensagem").textContent =
            `Correto! Você encontrou ${encontrada}!`;

        atualizarPalavras();
    } else {
        document.getElementById("mensagem").textContent =
            "Essa seleção não corresponde a uma palavra da lista. Tente novamente!";
    }
}

function pintarSelecao() {
    document.querySelectorAll("#grade button").forEach(botao => {
        botao.style.outline = "none";
        botao.style.background = "white";
    });

    if (primeira) {
        const [l, c] = primeira;

        const botao = document.querySelector(
            `#grade button[data-linha="${l}"][data-coluna="${c}"]`
        );

        if (botao) {
            botao.style.background = "#ffe082";
            botao.style.outline = "2px solid #d89b00";
        }
    }
}

function iniciarSequencia() {
    indiceNivelAtual = 0;

    if (nivel) {
        nivel.value = "facil";
    }

    prepararJogo(ordemNiveis[indiceNivelAtual]);

    window.scrollTo({
        top: 0,
        behavior: "smooth"
    });
}

botaoIniciar.addEventListener("click", iniciarSequencia);
