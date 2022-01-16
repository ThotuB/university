import { Google, Twitter } from 'components/common/svg/Icons'
import { useUser } from 'contexts/UserContext'
import Router from 'next/router'
import { useState } from 'react'

export default function SocialAuth() {
    const { user, logInGoogle, logInTwitter } = useUser()

    const [loadingGoogle, setLoadingGoogle] = useState(false)

    const handleGoogleLogin = async () => {
        try {
            await logInGoogle()
            Router.push('/home')
        }
        catch (error) {
            console.log(error)
        }
    }

    const handleTwitterLogin = async () => {
        try {
            await logInTwitter()
            Router.push('/home')
        }
        catch (error) {
            console.log(error)
        }
    }

    return (
        <div className="flex items-center mt-6 -mx-2">
            <button className="flex items-center justify-center w-full px-6 py-2 mx-2 text-sm font-medium text-white transition-colors duration-200 transform bg-blue-500 rounded-md hover:bg-blue-400"
                onClick={handleGoogleLogin}
            >
                <Google />
                <div className="hidden mx-2 sm:inline">Sign in with Google</div>
            </button>

            <button className="p-2 mx-2 text-sm font-medium text-gray-500 transition-colors duration-200 transform bg-gray-300 rounded-md hover:bg-gray-200"
                onClick={handleTwitterLogin}
            >
                <Twitter />
            </button>
        </div>
    );
}
