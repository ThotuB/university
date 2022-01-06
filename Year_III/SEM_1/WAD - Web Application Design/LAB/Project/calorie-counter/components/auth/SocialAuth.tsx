import { Google, Twitter } from 'components/common/svg/Icons'

export default function SocialAuth() {
    return (
        <div className="flex items-center mt-6 -mx-2">
            <button className="flex items-center justify-center w-full px-6 py-2 mx-2 text-sm font-medium text-white transition-colors duration-200 transform bg-blue-500 rounded-md hover:bg-blue-400 focus:bg-blue-400 focus:outline-none">
                <Google />
                <div className="hidden mx-2 sm:inline">Sign in with Google</div>
            </button>

            <button className="p-2 mx-2 text-sm font-medium text-gray-500 transition-colors duration-200 transform bg-gray-300 rounded-md hover:bg-gray-200" >
                <Twitter />
            </button>
        </div>
    );
}
