import AuthField from "./AuthField";

function LoginAuth() {
    return (
      <form className="mt-6 flex flex-col gap-4">
        <AuthField htmlFor="username" type="text">
          Username
        </AuthField>
        <AuthField htmlFor="email" type="text">
          Email
        </AuthField>
        <AuthField htmlFor="password" type="password">
          Password
        </AuthField>
        <AuthField htmlFor="confirm-password" type="password">
          Confirm Password
        </AuthField>

        <button className="mt-2 w-full px-4 py-2 tracking-wide text-white transition-colors duration-200 transform bg-gray-700 rounded-md hover:bg-gray-600 focus:outline-none focus:bg-gray-600">
          Create Account
        </button>
      </form>
    );
}

export default LoginAuth;