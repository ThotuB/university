import 'tailwindcss/tailwind.css'
import Head from 'next/head'
import type { AppProps } from 'next/app'

export default function MyApp({ Component, pageProps }: AppProps) {
    return (
        <>
            <Head>
                <title>Calorie Counter</title>
                <link rel="icon" href="/favicon.ico" />
                <link href="https://fonts.googleapis.com/css2?family=Readex+Pro:wght@300&family=Roboto:wght@300&display=swap" rel="stylesheet"></link>
            </Head>
            <div>
                <Component {...pageProps} />
            </div>
        </>
    );
}