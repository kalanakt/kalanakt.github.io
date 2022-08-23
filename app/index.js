AOS.init();

$(".navbar-burger").click(function () {
    $(".navbar-burger, .navbar-menu").toggleClass("is-active");
});
$(".navbar-item").click(() => {
    $(".navbar-burger, .navbar-menu").removeClass("is-active");
});

$.get("https://api.github.com/users/kalanakt").then((resp) => {
    $("#github-info").html(`
    <article class="media m-4">
    <figure class="media-left">
        <p class="image is-128x128">
            <img class="is-rounded" src="${resp.avatar_url}" />
        </p>
    </figure>
    <div class="media-content">
        <div class="content">
            <p>
                <strong>${resp.name || resp.login}</strong> <a href="${resp.html_url}"><small>@${resp.login}</small></a>
                <br />
                ${resp.bio}
            </p>
        </div>
    </div>
    
</article>
<nav class="level is-mobile">
    <div class="level-item has-text-centered">
        <div>
            <p class="heading">Repos</p>
            <p class="title is-5">${resp.public_repos}</p>
        </div>
    </div>
    <div class="level-item has-text-centered">
        <div>
            <p class="heading">Followers</p>
            <p class="title is-5">${resp.followers}</p>
        </div>
    </div>
    <div class="level-item has-text-centered">
        <div>
            <p class="heading">Following</p>
            <p class="title is-5">${resp.following}</p>
        </div>
    </div>
</nav>`);
});

function showRepoSlider() {
    $.get("https://api.github.com/users/kalanakt/repos").then((resp) => {
        let repo_cards = "";
        resp.sort((a, b) => (a.stargazers_count > b.stargazers_count ? -1 : 1));
        var repo_slider = new Splide("#repo-slider", {
            autoplay: true,
            pauseOnHover: true,
            interval: 1800,
            rewind: true,
            perMove: 1,
            perPage: 3,
            gap: "3em",
            breakpoints: {
                1024: {
                    perPage: 3
                },
                900: {
                    perPage: 2
                },
                640: {
                    perPage: 1
                }
            }
        }).mount();
        resp.forEach((repo) => {
            repo_slider.add(`<div class="splide__slide m-3" data-aos="zoom-in">
            <div class="box">
                <div class="content">
                    <p>
                        ${repo.fork ? `<i class="fas fa-code-branch"></i>` : `<i class="fas fa-book"></i>`} <a href="${repo.html_url}"><strong>${repo.name}</strong></a>
                        <br />
                        ${repo.description || "No description available"}
                    </p>
                </div>
                <nav class="level is-mobile">
                    <div class="level-left">
                        <span class="level-item" aria-label="reply"> <i class="fas fa-code" style="color: #1877f2"></i>&nbsp;${repo.language || "Viper"}</span>
                        <span class="level-item" aria-label="reply"> <i class="fas fa-star" style="color: #ff7300"></i>&nbsp;${repo.stargazers_count}</span>
                        <span class="level-item" aria-label="reply"> <i class="fas fa-code-branch" style="color: #6000df"></i>&nbsp;${repo.forks_count}</span>
                    </div>
                </nav>
            </div>
        </div>`);
        });
        // $("#repo_list").html(repo_cards);
    });
}

var mybutton = document.getElementById("scroll-up");
window.onscroll = function () {
    if (document.body.scrollTop > 400 || document.documentElement.scrollTop > 400) {
        mybutton.style.display = "block";
    } else {
        mybutton.style.display = "none";
    }
};

function scrollToTop() {
    document.body.scrollTop = 0;
    document.documentElement.scrollTop = 0;
}

new Splide("#image-slider", {
    autoplay: true,
    pauseOnHover: true,
    interval: 1600,
    rewind: true,
    perMove: 1,
    perPage: 3,
    gap: "3em",
    breakpoints: {
        1024: {
            perPage: 3
        },
        900: {
            perPage: 2
        },
        640: {
            perPage: 1
        }
    }
}).mount();


window.onload = () => {
    showRepoSlider()
}