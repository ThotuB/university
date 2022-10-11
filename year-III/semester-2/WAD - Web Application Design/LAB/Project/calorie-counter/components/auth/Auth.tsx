import LoginAuth from './LoginAuth';
import CreateAuth from './CreateAuth';
import SocialAuth from './SocialAuth';
import AuthFooter from './AuthFooter';
import { useState } from 'react';

export default function Auth() {
    const [isLogin, setIsLogin] = useState(true);

    const toggleAuth = () => {
        setIsLogin(!isLogin);
    };

    return (
        <div className='h-full w-full mt-56'>
            <div className='w-full max-w-sm p-6 m-auto bg-white rounded-xl shadow-md flex flex-col border'>
                <div className='text-3xl font-semibold text-center text-gray-700'>
                    Calorie Counter
                </div>

                {isLogin ? <LoginAuth /> : <CreateAuth />}

                <Divider />

                <SocialAuth />

                <AuthFooter
                    onClick={toggleAuth}
                    text={
                        isLogin
                            ? "Don't have an account? "
                            : 'Already have an account? '
                    }
                    label={isLogin ? 'Create One' : 'Login'}
                />
            </div>
        </div>
    );
}

const Divider = () => (
    <div className='flex items-center justify-between mt-4'>
        <div className='w-1/5 border-b dark:border-gray-600 lg:w-1/5' />

        <div className='text-xs text-center text-gray-500 uppercase dark:text-gray-400'>
            or login with Social Media
        </div>

        <div className='w-1/5 border-b dark:border-gray-400 lg:w-1/5' />
    </div>
);
