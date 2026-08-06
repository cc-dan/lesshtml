# lesshtml
A tool for writing less HTML. Functions similar to a simple static site generator.

## Usage
A lesshtml project directory consists of a `src` folder with your HTML project and an `html_components` file that describes the reusable components featured in the HTML files. Executing `lesshtml` in this directory will generate a `gen` folder identical in structure to `src` but with every HTML file processed and minified (including CSS).

## Example

The content of `html_components` could be as follows:

```
metadata {
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="/style.css">
    <link rel="icon" href="/favicon.ico" type="image/x-icon">
}

header {
    <header id="header">
        <div class="box" id="title"><a href="/">my site</a></div>
        <nav>
            <a href="/">index</a>
            <a href="/articles.html">articles</a>
            <a href="/games.html">games</a>
        </nav>
    </header>
}

footer {
    <footer id="footer">
        <p>copyright whatever</p>
    </footer>
}
```

The components are used in the HTML files as so:

```html
<!DOCTYPE html>
<html lang="en">
    <head>
        <!component metadata>
        <title>my site</title>
    </head>
    <body>
        <!component header>

        <main>
            <p>page content</p>
        </main>

        <!component footer>
    </body>
</html>
```

Components can also be used inside other components:

```
site-name {
    my site
}

header {
    <header id="header">
        <h1><!component site-name></h1>
    </header>
}
```
