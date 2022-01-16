import { EyeIcon, EyeOffIcon } from '@heroicons/react/outline';
import Button from 'components/common/Button';
import TextField from 'components/common/TextField';
import Router from 'next/router';
import { useState } from 'react';
import { useUser } from 'contexts/UserContext';

export default function LoginAuth() {
    const [email, setEmail] = useState('');
    const [password, setPassword] = useState('');

    const [showPassword, setShowPassword] = useState(false);
    const [loading, setLoading] = useState(false);

    const { user, logIn } = useUser();

    const handleLogin = async () => {
        setLoading(true);

        try {
            await logIn(email, password);
            Router.push('/home');
        }
        catch (error) {
            console.error(error);
        }

        setLoading(false);
    }

    return (
        <form className="mt-6 flex flex-col gap-4"
            onSubmit={e => e.preventDefault()}
        >
            <TextField label='Email' type="text"
                value={email}
                onChange={(event) => setEmail(event.target.value)}
                maxLength={50}
                required
            />

            <div className="relative">
                <div className="w-full absolute">
                    <a href="#" className="text-xs float-right text-gray-600 hover:underline" >
                        Forget Password?
                    </a>
                </div>

                <div className='flex gap-2'>
                    <TextField label='Password' type={showPassword ? 'text' : 'password'}
                        value={password}
                        onChange={(event) => setPassword(event.target.value)}
                        maxLength={20}
                        required
                    />
                    <button onClick={() => setShowPassword(!showPassword)}>
                        {showPassword ? <EyeIcon className="w-6 pt-7" /> : <EyeOffIcon className="w-6 pt-7" />}
                    </button>
                </div>
            </div>

            {loading ?
                <div className='px-3 py-2 font-bold rounded-md text-white bg-gray-600 text-center'>
                    Sign In
                </div> :
                <Button onClick={handleLogin}>
                    Sign In
                </Button>
            }
        </form>
    );
}