import 'tailwindcss/tailwind.css'
import Head from 'next/head'
import type { AppProps } from 'next/app'
import { UserProvider } from 'contexts/UserContext';

export default function MyApp({ Component, pageProps }: AppProps) {
    return (
        <UserProvider>
            <Head>
                <title>Calorie Counter</title>
                <link rel="icon" href="/favicon.ico" />
                <link href="https://fonts.googleapis.com/css2?family=Readex+Pro:wght@300&family=Roboto:wght@300&display=swap" rel="stylesheet" />
                <link href="//db.onlinewebfonts.com/c/31aefc600de86877c5f9f991836a7fbb?family=FuturaBTW01-Book" rel="stylesheet" type="text/css" />
                <link href="//db.onlinewebfonts.com/c/b8304efa3274630d292cdce9cad53bb5?family=FuturaBTW01-Light" rel="stylesheet" type="text/css" />
            </Head>
            <div className="font-site">
                <Component {...pageProps} />
            </div>
        </UserProvider>
    );
}