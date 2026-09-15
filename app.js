const form = document.getElementById("loginForm");
const result = document.getElementById("result");

form.addEventListener("submit", async (event) => {

    event.preventDefault();

    const username =
        document.getElementById("username").value;

    const password =
        document.getElementById("password").value;

    const passwordEntered =
        password.length > 0;

    try {

        await fetch("/api/login-event", {
            method: "POST",

            headers: {
                "Content-Type":
                    "application/x-www-form-urlencoded"
            },

            body:
                "username=" +
                encodeURIComponent(username) +
                "&password_entered=" +
                passwordEntered
        });

    } catch (error) {

        console.log(
            "Lab event endpoint unavailable."
        );

    }

    /*
     * IMPORTANT:
     *
     * The password value is intentionally
     * never transmitted or stored.
     */

    document.getElementById("password").value = "";

    form.style.display = "none";
    result.classList.remove("hidden");

});